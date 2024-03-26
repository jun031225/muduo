#include "EPollPoller.h"
#include "Logging.h"
#include "Channel.h"
#include "EventLoop.h"

#include <assert.h>

// channel的状态index_(未监视，被监视，被移除)
const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;

EPollPoller::EPollPoller(EventLoop *loop) :ownerLoop_(loop),
                                            epollfd_(::epoll_create(EPOLL_CLOEXEC)),
                                            events_(kInitEventListSize)
{
    if (epollfd_ < 0)
    {
        LOG_FATAL << "epoll_create() error" << errno;
    }
    else
    {
        LOG_DEBUG << "create a new epollfd, fd = " << epollfd_;
    }
}

EPollPoller::~EPollPoller()
{
    ::close(epollfd_);
}

//epoll_wait并设置epollpoller的activechannel和channel的revents_
TimeStamp EPollPoller::poll(int timeoutMs, ChannelList* activeChannels)
{
    size_t numEvents = ::epoll_wait(epollfd_, &(*events_.begin()), static_cast<int>(events_.size()), timeoutMs);
    int saveErrno = errno;//保存错误信息，防止被改变
    TimeStamp now(TimeStamp::now());

    //有事件发生
    if(numEvents > 0)
    {
        fillActiveChannels(numEvents, activeChannels);
        //扩容vector<epoll_event>2倍
        if(numEvents == events_.size())
        {
            events_.resize(events_.size()*2);
        }
    }
    //超时
    else if(numEvents == 0)
    {
        LOG_TRACE << "timeout!";
    }
    //出错
    else
    {
        if(saveErrno != EINTR)
        {
            errno = saveErrno;
            LOG_ERROR << "EpollPoller::poll() faild!";
        }
    }
    return now;
}

//将发生事件的channel添加进activeChannels数组并设置channel的revents_属性
void EPollPoller::fillActiveChannels(int numEvents, EPollPoller::ChannelList *activeChannels) const
{
    for(int i=0 ;i<numEvents;++i)
    {
        Channel *channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel);
    }
}

//将channel添加到epollpoller(epoll_ctl)并设置channel的状态
void EPollPoller::updateChannel(Channel *channel)
{
    //只添加未添加和已移除状态的channel
    const int index =  channel->index();
    if(index == kNew || index == kDeleted)
    {
        int fd = channel->fd();
        if(index == kNew)
        {
            channels_[fd] = channel; //unordered_map<int, Channel*>
        }
        else//index == kDEleted
        {
            assert(channels_.find(fd) != channels_.end());
            assert(channels_[fd] == channel);
        }

        channel->set_index(kAdded);
        EPollPoller::update(EPOLL_CTL_ADD, channel);
    }
    else//channel已注册到epollpoller
    {
        //无感兴趣的事件
        if(channel->isNoneEvent())
        {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        }
        //事件被修改
        else
        {
            update(EPOLL_CTL_MOD,channel);
        }
    }
}


void EPollPoller::update(int operation, Channel* channel)
{
    epoll_event event;
    ::memset(&event, 0 ,sizeof(event));

    int fd = channel->fd();
    event.events = channel->events();

    event.data.ptr = channel;

    if(::epoll_ctl(epollfd_, operation, fd, &event) < 0)
    {
        if(operation ==  EPOLL_CTL_DEL)
        {
            LOG_ERROR << "epoll_ctl_del error :" << errno;
        }
        else{
            LOG_ERROR << "epoll_ctl_add/mod error :" << errno;
        }
    }
}

//当连接销毁时，从epoll中移除并改变channel的状态，
void EPollPoller::removeChannel(Channel* channel)
{
    //从map中移除
    int fd = channel->fd();
    channels_.erase(fd);

    int index = channel->index();
    if(index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);
}

//判断channel是否被注册到epoll中
bool EPollPoller::hasChannel(Channel *channel) const
{
    auto it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}

int main()
{
    std::cout<<"test";
    return 0;
}