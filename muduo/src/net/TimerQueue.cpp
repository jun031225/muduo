#include "TimerQueue.h"
#include "EventLoop.h"
#include "Timer.h"
#include "Logging.h"

#include <sys/timerfd.h>
#include <unistd.h>
#include <string.h>

// timerfd_create创建timerfd-->epoll注册timerfd-->timerfd_settime启动定时器
//-->timerfd可读-->TimerQueue::handleRead-->
// 一个timerfd实现多个定时器(让timerfd的超时时刻总是设置为TimerQueue中最小的Timer的超时时刻)

// 创建timerfd
int createTimerfd()
{
    // CLOCK_MONOTONIC表示绝对时间（最近一次重启到现在的时间，会因为系统时间的更改而变化）
    // CLOCK_REALTIME表示从1970.1.1到目前时间（更该系统时间对其没影响）
    // TFD_NONBLOCK(设置timerfd非阻塞)，TFD_CLOEXEC（fork子进程后在子进程中关掉父进程打开的文件描述符）
    int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    LOG_DEBUG << "create a timerfd, fd =" << timerfd;
    if (timerfd < 0)
    {
        LOG_ERROR << "Failed in tiemrfd_create!";
    }
    return timerfd;
}

// 开启或停止定时器
//  重置timerfd的超时时间，重置后，如果超时时间不为0，则内核会启动定时器，否则内核会停止定时器
void resetTimerfd(int timerfd, TimeStamp expiration)
{
    /*
       struct timespec {
       time_t tv_sec;                // 秒
       long   tv_nsec;               // 纳秒
   };

   struct itimerspec {
       struct timespec it_interval;  // 定时器超时时间间隔
       struct timespec it_value;     // 初始过期时间
   };
   */
    // 初始化为空
    struct itimerspec newValue;
    struct itimerspec oldValue;
    memset(&newValue, '\0', sizeof(newValue));
    memset(&oldValue, '\0', sizeof(oldValue));

    // 计算超时时间(相对)（超时时刻-现在时刻）
    int64_t interval = expiration.microSecondsSinceEpoch() - TimeStamp::now().microSecondsSinceEpoch();
    if (interval < 100)
    {
        interval = 100;
    }

    struct timespec ts;
    ts.tv_sec = static_cast<time_t>(interval / TimeStamp::microSecondPerSecond);         // 秒
    ts.tv_nsec = static_cast<long>((interval % TimeStamp::microSecondPerSecond) * 1000); // 微秒
    newValue.it_value = ts;

    // int timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value);
    //  调用timerfd_settime启动定时器,唤醒事件循环
    if (::timerfd_settime(timerfd, 0, &newValue, &oldValue))
    {
        LOG_ERROR << "timerfd_settime failed!";
    }
}

void readTimerfd(int timerfd)
{
    uint64_t buf;
    ssize_t ret = ::read(timerfd, &buf, sizeof(buf));
    if (ret != sizeof(buf))
    {
        LOG_ERROR << "TimerQueue::handleRead() reads " << ret << "bytes instead of 8";
    }
}

TimerQueue::TimerQueue(EventLoop *loop)
    : loop_(loop),
      timerfd_(createTimerfd()),
      timerfdChannel_(loop_, timerfd_), // 绑定Chnnel(fd)与EventLoop
      timers_()
{
    // 为timerfd的可读事件设置回调函数并向epoll中注册timerfd的可读事件
    timerfdChannel_.setReadCallback(std::bind(&TimerQueue::handleRead, this));
    timerfdChannel_.addReading();
}

TimerQueue::~TimerQueue()
{
    timerfdChannel_.delAll();
    timerfdChannel_.remove();
    ::close(timerfd_);

    // 删除定时器
    for (const Entry &timer : timers_)
    {
        delete timer.second;
    }
}

// 向定时器队列添加定时器
void TimerQueue::addTimer(TimerCallback cb, TimeStamp when, double interval)
{
    Timer *timer = new Timer(std::move(cb), when, interval);
    loop_->runInLoop(std::bind(&TimerQueue::addTimerInLoop, this, timer));
}

void TimerQueue::addTimerInLoop(Timer *timer)
{
    // 将timer添加到TimerList时，判断其超时时刻是否是最早的
    bool eralistChanged = TimerQueue::insert(timer);

    // 重置定时器
    if (eralistChanged)
    {
        resetTimerfd(timerfd_, timer->expiration());
    }
}

// 重置超时的定时器(插入可重复->重置、删除不可重复)
void TimerQueue::resetExpired(const std::vector<Entry> &expiredTimers, TimeStamp now)
{
    TimeStamp nextExpire; // 记录timerfd下一次超时时刻
    for (const Entry &it : expiredTimers)
    {
        if (it.second->repeat()) // 定时器可重复,插入定时器队列
        {
            auto timer = it.second;
            timer->restart(TimeStamp::now()); // 设置下一次超时时刻
            TimerQueue::insert(timer);
        }
        else
        {
            delete it.second;
        }
    }
    // 重置timerfd的初始超时时间
    if (!timers_.empty())
    {
        nextExpire = timers_.begin()->second->expiration();
    }
    if (nextExpire.valid())
    {
        resetTimerfd(timerfd_, nextExpire);
    }
}

// 处理超时的定时器
void TimerQueue::handleRead()
{
    TimeStamp now = TimeStamp::now();
    readTimerfd(timerfd_);

    // 获取超时的定时器并逐个调用回调函数
    std::vector<Entry> expiredTimers = getExpiredTimers(now);
    callingExpriedTimers_ = true;
    for (const Entry &it : expiredTimers)
    {
        it.second->run();
    }
    callingExpriedTimers_ = false;
    // 重置超时的定时器
    resetExpired(expiredTimers, now);
}

// 插入新的定时器并返回是否是最早到期定时器
bool TimerQueue::insert(Timer *timer)
{
    bool eralistChanged = false;
    TimeStamp when = timer->expiration();
    TimerList::iterator it = timers_.begin();

    if (it == timers_.end() || when < it->first) // 定时器队列为空/小于最早到期的定时器
    {
        eralistChanged = true;
    }
    // 插入新的定时器
    timers_.insert(Entry(when, timer)); // set::insert
    return eralistChanged;
}

// 移除所有已到期的定时器
// 1.获取到期的定时器
// 2.重置这些定时器（销毁或者重复定时任务）
std::vector<TimerQueue::Entry> TimerQueue::getExpiredTimers(TimeStamp now)
{
    std::vector<Entry> expiredTimers;
    Entry sentry(now, reinterpret_cast<Timer *>(UINTPTR_MAX));

    // lower_bound返回第一个大于等于sentry的迭代器，
    // 这里的意思是在TimerList中找到第一个没有超时的迭代器
    TimerList::iterator end = timers_.lower_bound(sentry);

    // 把TimerList中所有超时的元素都拷贝到expiredTimer中
    std::copy(timers_.begin(), end, back_inserter(expiredTimers));

    timers_.erase(timers_.begin(), end); // 移除超时定时器

    return expiredTimers;
}
