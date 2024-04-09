#pragma once

#include"EventLoopThread.h"
#include"EventLoop.h"

EventLoopThread::EventLoopThread(const ThreadInitCallback &cb, const std::string &name)
:loop_(nullptr),
exiting_(false),
thread_(std::bind(&EventLoopThread::threadFunc, this), name),
mutex_(),
cond_(),
callback_(cb)
{}

EventLoopThread::~EventLoopThread()
{
    exiting_ = true;
    if(loop_ != nullptr)
    {
        loop_->quit();//退出事件循环
        thread_.join();
    }
}

EventLoop*  EventLoopThread::startLoop()
{
    // 启动一个新线程。在构造函数中，thread_已经绑定了回调函数threadFunc
    // 此时，子线程开始执行threadFunc函数
    thread_.start();

    EventLoop *loop = nullptr;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        //等待新线程执行创建EventLoop完毕
        while(loop_ == nullptr)
        {
            cond_.wait(lock);
        }
        loop = loop_;
    }
    return loop;
}

void EventLoopThread::threadFunc()
{
    EventLoop loop;
    //线程初始化完成后执行回调函数
    if(callback_)
    {
        callback_(&loop);
    }

    {
        std::unique_lock<std::mutex> lock(mutex_);
        loop_ = &loop;
        cond_.notify_one();// 生成EventLoop对象之后唤醒主线程，即startLoop()函数才能继续执行
    }

    loop.loop();//执行subLoop事件循环
    std::unique_lock<std::mutex> lock(mutex_);
    loop_ = nullptr;//关闭loop_
}

