#include"EventLoopThreadPool.h"
#include"EventLoopThread.h"
#include"EventLoop.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop *baseloop, const std::string &nameArg)
:baseloop_(baseloop),
name_(nameArg),
started_(false),
numThreads_(0),
next_(0)
{}

EventLoopThreadPool::~EventLoopThreadPool()
{

}

//开启线程池
void EventLoopThreadPool::start(const ThreadInitCallback &cb)
{
    started_ = true;

    //循环创建线程
    for(int i = 0; i < numThreads_; ++i)
    {
        char buf[name_.size() + 32];
        snprintf(buf, sizeof(buf), "%s%d", name_.c_str(), i);

        EventLoopThread *t = new EventLoopThread(cb,buf);//创建线程
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));//加入线程池
        loops_.push_back(t->startLoop());//绑定并执行事件循环，加入事件循环集合
    }

    if(numThreads_ == 0 && cb)
    {
        cb(baseloop_);
    }
}

// 采用轮询方式分发subReactor
EventLoop* EventLoopThreadPool::getNextLoop()
{
    EventLoop *loop = baseloop_;

    //有subReactor
    if(!loops_.empty())
    {
        loop =loops_[next_];
        ++next_;

        //轮询
        if(next_ >= loops_.size())
        {
            next_ = 0;
        }
    }
    return loop;
}


//获取线程池中所有事件循环对象的指针
std::vector<EventLoop*> EventLoopThreadPool::getAllLoops()
{
    if(loops_.empty())
    {
        return std::vector<EventLoop*>(1, baseloop_);
    }
    else
    {
        return loops_;
    }
}