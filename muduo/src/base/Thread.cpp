#include "Thread.h"
#include "CurrentThread.h"

#include <semaphore.h>

std::atomic_int32_t Thread::numCreated_(0);

Thread::Thread(ThreadFunc func, const std::string &name)
    : started_(false),
      joined_(false),
      tid_(0),
      func_(std::move(func)),
      name_(name)
{
    setDefaultName();
}

Thread::~Thread()
{
    //线程启动且非连接
    if(started_ && !joined_)
    {
        thread_->detach();//分离线程，结束自动释放资源
    }
}

void Thread::start()
{
    started_ = true;
    sem_t sem;
    sem_init(&sem, false, 0);
    //创建新线程
    thread_ = std::shared_ptr<std::thread>(new std::thread([&](){
        tid_ = CurrentThread::tid();//获取线程id
        sem_post(&sem);//新线程调用，信号量加1
        func_();
    }));
    //其他线程需要等待直到新创建线程获取到tid后，避免没有获取tid其他线程就访问其tid
    sem_wait(&sem);//其他线程等待，减少信号量
}

void Thread::join()
{
    joined_ = true;
    thread_->join();
}

//设置线程名 Thread numCreated
void Thread::setDefaultName()
{
    int num = ++numCreated_;
    if(name_.empty())
    {
        char buf[32] = {0};
        snprintf(buf, sizeof(buf), "Thread%d", num);
        name_ = buf;
    }
}