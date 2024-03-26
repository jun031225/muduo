#include "EventLoop.h"
#include "Channel.h"
#include "EPollPoller.h"
#include "TimerQueue.h"

#include <sys/eventfd.h>

//__thread 是一个线程局部存储（TLS）的关键字，
// 当你在一个变量声明前面加上 __thread 关键字时，这个变量就会变成每个线程有自己独立实例的变量，
// 每个线程对这个变量的读写操作都只会影响到线程自己的实例，不会影响到其他线程的实例
//__thread 关键字只能用于静态生存期的变量，包括全局变量、静态变量和静态成员变量。它不能用于函数的局部变量或者类的非静态成员变量。
// 这个变量被初始化为 nullptr，表示它一开始不指向任何 EventLoop 对象。在线程启动时，
// 我们在该线程执行函数中构造一个 EventLoop 对象，并把 t_loopInThisThread 初始化为指向这个对象的指针
// 这样，每个线程就可以通过 t_loopInThisThread 访问到自己的 EventLoop 对象,从而确保一个线程只有一个eventloop
__thread EventLoop *t_loopInThisThread = nullptr;

const int kPollTimeMs = 10000; // 默认epoller I/O复用接口超时时间

int createEventfd()
{
    int evfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evfd < 0)
        LOG_FATAL << "eventfd error:" << errno;
    else
        LOG_DEBUG << "create a new wakeupfd, fd = " << evfd;
    return evfd;
}

EventLoop::EventLoop() : looping_(false),
                         quit_(false),
                         callingPendingFunctors_(false),
                         threadID_(CurrentThread::tid()),
                         epoller_(new EPollPoller(this)),
                         timerQueue_(new TimerQueue(this)),
                         wakeupFd_(createEventfd()),
                         wakeupChannel_(new Channel(this, wakeupFd_))
{
    LOG_DEBUG << "EventLoop created" << this << ", the threadID is" << threadID_;
    if (t_loopInThisThread)
    {
        LOG_FATAL << "Another EventLoop" << t_loopInThisThread << "exists in this thread" << threadID_;
    }
    else
    {
        t_loopInThisThread = this;
    }
    // 设置wakeupChannel_可读事件的回调函数，并向当前loop的EPoller中注册可读事件
    wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
    wakeupChannel_->addReading();
}

EventLoop::~EventLoop()
{
    wakeupChannel_->delAll();
    wakeupChannel_->remove();
    ::close(wakeupFd_);
    t_loopInThisThread = nullptr;
}

void EventLoop::loop()
{
    looping_ = true;
    quit_ = false;
    LOG_INFO << "EventLoop" << this << "start looping!";

    while (!quit_)
    {
        activeChannels_.clear();
        epollReturnTime_ = epoller_->poll(kPollTimeMs, &activeChannels_);
        // 循环等待事件发生
        for (Channel *channel : activeChannels_)
        {
            channel->handleEvent(epollReturnTime_);
        }
        /**
         * 执行当前EventLoop事件循环需要处理的回调操作 对于线程数 >=2 的情况 IO线程 mainloop(mainReactor) 主要工作：
         * accept接收连接 => 将accept返回的connfd打包为Channel => TcpServer::newConnection通过轮询将TcpConnection对象分配给subloop处理
         * mainloop调用queueInLoop将回调加入subloop的pendingFunctors_中（该回调需要subloop执行 但subloop还在epoller_->poll处阻塞）
         * queueInLoop通过wakeup将subloop唤醒，此时subloop就可以执行pendingFunctors_中的保存的函数了
         **/
        // 执行其他线程添加到pendingFunctors_中的函数
        doPendingFunctors();
    }
    looping_ = false;
}

void EventLoop::quit()
{
    quit_ = true;
    if (!isInLoopThread())
        wakeup(); // 触发wakeupFd_可读事件，防止epoll_wait()阻塞导致无法退出Loop循环
}

// 对wakeupFd_进行写操作，触发读事件
void EventLoop::wakeup()
{
    uint64_t data = 1;
    ssize_t ret = write(wakeupFd_, &data, sizeof(data));
    if (ret != sizeof(data))
    {
        LOG_ERROR << "EventLoop::handleRead() reads" << ret << "bytes instead of 8";
    }
}

// 如果当前调用runInLoop的线程正好是EventLoop绑定的线程，则直接执行此函数,
// 否则就将回调函数通过queueInLoop()存储到pendingFunctors_中
void EventLoop::runInLoop(Functor cb)
{
    if (isInLoopThread())
        cb();
    else
        queueInLoop(cb);
}

// 把cb放入队列中 唤醒loop所在的线程执行cb
void EventLoop::queueInLoop(Functor cb)
{
    std::unique_lock<std::mutex> lock(mutex_);
    pendingFunctors_.emplace_back(cb);

    if (!isInLoopThread() || callingPendingFunctors_)
    {
        wakeup();
    }
}

// weakupChannel的回调函数
void EventLoop::handleRead()
{
    uint64_t data = 1;
    ssize_t ret = read(wakeupFd_, &data, sizeof(data));
    if (ret != sizeof(data))
    {
        LOG_ERROR << "EventLoop::handleRead() reads" << ret << "bytes instead of 8";
    }
}

// 注册事件(epoll_ctl_add)
void EventLoop::updateChannel(Channel *channel)
{
    epoller_->updateChannel(channel);
}

// 移除事件(epoll_ctl_del)
void EventLoop::removeChannel(Channel *channel)
{
    epoller_->removeChannel(channel);
}

// channel是否在epoller
bool EventLoop::hasChannel(Channel *channel)
{
    return epoller_->hasChannel(channel);
}

// 在time时刻执行回调函数
void EventLoop::runAt(TimeStamp time, Functor &&cb)
{
    timerQueue_->addTimer(std::move(cb), time, 0.0);
}

// 在delay秒后执行回调函数
void EventLoop::runAfter(double delay, Functor &&cb)
{
    TimeStamp time(addTime(TimeStamp::now(), delay));
    runAt(time, std::move(cb));
}

// 每隔interval秒执行一次回调函数
void EventLoop::runEvery(double interval, Functor &&cb)
{
    TimeStamp timestamp(addTime(TimeStamp::now(), interval));
    timerQueue_->addTimer(std::move(cb), timestamp, interval);
}

void EventLoop::doPendingFunctors()
{
    std::vector<Functor> functors;
    callingPendingFunctors_ = true;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        functors.swap(pendingFunctors_);
    }
    for (const Functor &functor : functors)
    {
        functor();
    }
    callingPendingFunctors_ = false;
}