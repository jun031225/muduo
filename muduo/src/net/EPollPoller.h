#pragma once

#include "noncopyable.h"
#include "TimeStamp.h"

#include <sys/epoll.h>
#include <unistd.h>
#include <vector>
#include <unordered_map>

class Channel;
class EventLoop;

// 对I/O多路复用epoll的封装，主要为系统调用epoll_creat，eepoll_ctl和epoll_wait 以及调用后 自身 与 事件对应channel 相关属性的更改
class EPollPoller : noncopyable
{
public:
    using ChannelList = std::vector<Channel *>;

    EPollPoller(EventLoop *loop);
    ~EPollPoller();

    // 内部调用epoll_wait,返回实际发生事件的channel到activeChannels
    TimeStamp poll(int timeoutMs, ChannelList *activeChannels);

    // 更新channel上感兴趣的事件(events_)
    void updateChannel(Channel *channel);

    // 连接销毁时，从epoller中移除channel
    void removeChannel(Channel *channel);

    // 判断channel是否注册到epoller中
    bool hasChannel(Channel *channel) const;

private:
    using ChannelMap = std::unordered_map<int, Channel *>; // fd到channel的映射
    using EventList = std::vector<epoll_event>;            // 存储有事件发生的channel
    /*
    struct epoll_event
    {
      uint32_t events;
       epoll_data_t data;
    };

    union epoll_data
    {
        void *ptr;
        int fd;
        uint32_t u32;
        uint64_t u64;
    };
    */

    // 把有事件发生的channel添加到activeChannels
    void fillActiveChannels(int numEvents, ChannelList *activeChannels) const;

    // 更新channel状态，本质调用epoll_ctl
    void update(int operation, Channel *channel);

    // 默认监听事件数量
    static const int kInitEventListSize = 16;

    ChannelMap channels_; // 储存channel映射，通过fd快速找到channel

    EventLoop *ownerLoop_; // epoller所属的事件循环EventLoop

    int epollfd_; // 内核事件表fd，每个EPollPoller都有一个epollfd_，epollfd_是epoll_create在内核创建空间返回的fd

    // 用于存放epoll_wait返回的所有发生的事件
    EventList events_;
};
