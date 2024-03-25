#pragma once

#include "TimeStamp.h"
#include "Channel.h"

#include <vector>
#include <set>

class EventLoop;
class Timer;

class TimerQueue : noncopyable
{
public:
    using TimerCallback = std::function<void()>;

    explicit TimerQueue(EventLoop *loop);
    ~TimerQueue();

    // 通过调用insert向TimerList中插入定时器（回调函数，到期时间，时间间隔）
    void addtimer(TimerCallback cb, TimeStamp when, double interval);

private:
    using Entry = std::pair<TimeStamp, Timer *>;
    // set内部是红黑树，删除，查找效率都很高，而且是排序的，set中放pair默认是按照pair的第一个元素进行排序
    // 即这里是按照Timestamp从小到大排序
    using TimerList = std::set<Entry>;

    EventLoop *loop_; // 所属事件循环
    // 当超时的时候，timerfd就变得可读。这种用文件描述符的方式可以注册到epoll中，以便和TCP连接上的IO事件统一处理。
    const int timerfd_;             // timerfd是Linux提供的定时器接口
    Channel timerfdChannel_;    // 封装timerfd_文件描述符
    TimerList timers_;          // 定时器队列(红黑树)
    bool callingExpriedTimers_; // 是否正在获取超时定时器

    void addTimerInLoop(Timer *timer);                            // 在当前事件循环(Eventloop)添加定时器
    void handleRead();                                            // 定时器读时间回调函数
    std::vector<Entry> getExpiredTimers(TimeStamp now);           // 获取到期的定时器
    void reset(const std::vector<Entry> &expired, TimeStamp now); // 重置到期(超时)的定时器(销毁或重启定时任务)
    bool insert(Timer *timer);                                    // 插入定时器
};