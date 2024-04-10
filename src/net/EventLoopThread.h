#pragma once

#include"noncopyable.h"
#include"Thread.h"

#include<mutex>
#include<condition_variable>

class EventLoop;

//这个类允许在一个单独的线程中创建并运行事件循环，并提供了一种机制来在初始化完成后执行特定的回调函数。
class EventLoopThread : noncopyable
{
    public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    EventLoopThread(const ThreadInitCallback &cb = ThreadInitCallback(), const std::string &name = std::string());
    ~EventLoopThread();

    EventLoop *startLoop();//开启新线程

    private:
    void threadFunc();//线程执行函数

    EventLoop *loop_;//子线程绑定的loop
    bool exiting_;
    Thread thread_;
    std::mutex mutex_;
    std::condition_variable cond_;// 条件变量, 主线程等待子线程创建EventLoop对象完成
    ThreadInitCallback callback_;//线程初始化完成执行的回调函数
};