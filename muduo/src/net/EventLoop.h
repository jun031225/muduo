#pragma once

#include"noncopyable.h"
#include "TimeStamp.h"
#include "CurrentThread.h"

#include <vector>
#include <atomic>
#include <memory>
#include <mutex>
#include <functional>

class Channel;
class EpollPoller;
class TimerQueue;


//持续循环的获取监听结果并且根据结果调用处理函数
class EventLoop : noncopyable
{
private:
    using ChannelList = std::vector<Channel *>;

    void handleRead();
    void doPendingFunctors();

    std::atomic_bool looping_;                // 是否正在事件循环中
    std::atomic_bool quit_;                   // 是否退出循环
    std::atomic_bool callingPendingFunctors_; // 是否正在调用待执行的函数
    const pid_t threadID_;                    // 当前loop所属的线程ID
    TimeStamp epollReturnTime_;               // 有事件发生时的时间(epoll_wait返回的时间)
    std::unique_ptr<EpollPoller> epoller_;
    std::unique_ptr<TimerQueue> timerQueue_; // 当前loop所有定时器的容器

    int wakeupFd_;                           // 用于唤醒epoller,避免epoller因阻塞无法执行pendingfunctors_中的待处理函数
    std::unique_ptr<Channel> wakeupChannel_; // wakeupFd_对应的channel
    ChannelList activeChannels_;             // 发生事件的Channel集合
    std::mutex mutex_;                       // 用于保护pendingFunctors_线程安全操作(添加或取出)
    std::vector<Functor> pendingFunctors_;   // 存储loop跨线程需要执行的所有回调操作
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    void loop();
    void quit();

    TimeStamp epollReturnTime() const { return epollReturnTime_; } // epoll_wait()返回时的时间

    void runInLoop(Functor cb);   // 让回调函数在eventloop绑定的线程中执行
    void queueInLoop(Functor cb); // 让回调函数cb添加到EventLoop的pendingFunctors_中，以便以后在在EventLoop绑定的线程中执行

    void wakeup(); // 唤醒epollpoller，避免因epoll_wait(poll)导致阻塞,方式为向wakeupFd_写入数据，发生可读事件

    void updateChannel(Channel *channel); // 更新epollpoller中感兴趣的事件
    void removeChannel(Channel *channel); // 从epoller移除事件

    bool hasChannel(Channel *channel); // 判断channel是否在当前eventloop中

    // 判断EventLoop初始化时绑定的线程id是否和当前正在运行的线程id是否一致
    bool isInLoopThread() const { return threadID_ == CurrentThread::tid(); }

    void  runAt(TimeStamp time, Functor&& cb);//在time时刻执行回调函数
    void runAfter(double delay, Functor &&cb);//在 delay秒后执行回调函数
    void runEvery(double interval, Functor &&cb);//每隔interval秒执行一次回调函数
};