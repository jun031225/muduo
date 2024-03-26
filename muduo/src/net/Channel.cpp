#include "Channel.h"
#include "EventLoop.h"

#include <sys/epoll.h>


const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop *loop, int fd) : loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1), tied_(false) {}

Channel::~Channel()
{
    if (loop_->isInLoopThread())
    {
        assert(!loop_->hasChannel(this));
    }
}

void Channel::tie(const std::shared_ptr<void> &obj)
{
    tie_ = obj; // 让tie_(weak_ptr)指向obj，后边处理fd上发生的事件时，就可以用tie_判断TcpConnection是否还活着
    tied_ = true;
}

// 注册/删除事件
void Channel::update()
{
    loop_->updateChannel(this);
}

// 把事件从epollpoller移除
void Channel::remove()
{
    loop_->removeChannel(this);
}

void Channel::handleEvent(TimeStamp receiveTime)
{
    if (tied_)
    {
        std::shared_ptr<void> guard = tie_.lock();
        if (guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }
}

void Channel::handleEventWithGuard(TimeStamp receiveTime)
{
    // 对方关闭连接
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if (closeCallback_) closeCallback();
    }
    // 错误事件
    if (revents_ & EPOLLERR)
    {
        if (errorCallback_) errorCallback();
    }
    //可读事件(普通数据，高优先数据，关闭连接请求)
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        if (readCallback_) readCallabck();
    }
    //可写事件
    if(revents_ & EPOLLOUT)
    {
        if(writeCallback_) writeCallback();
    }
}