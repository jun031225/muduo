#pragma once

#include "noncopyable.h"
#include "Thread.h"
#include "FixedBuffer.h"
#include "LogStream.h"
#include "LogFile.h"

#include <vector>
#include <memory>
#include <mutex>
#include <condition_variable>

class AsyncLogging : noncopyable
{
    AsyncLogging(const std::string &basename, off_t rollSize, int flushInterval = 3);
    ~AsyncLogging();

    void append(const char *logline, int len);

//创建工作线程
    void start()
    {
        running_ = true;
        thread_.start();
    }

//
    void stop()
    {

        running_ = false;
        cond_.notify_one();
    }
private:
    using Buffer = FixedBuffer<kLargeBUffer>; //后端缓冲区Buffer(4MB)

    // BufferVector存储独占指针的目的是：从BufferVector中弹出元素（Buffer）后会自动析构
    using BufferVector = std::vector<std::unique_ptr<Buffer>>;//缓冲(4MB)队列
    using BufferPtr = BufferVector::value_type;//缓冲区(4MB)指针

    void threadFunc();//线程函数

    const int flushInterval_;//刷新间隔
    std::atomic<bool> running_;//线程是否运行
    const std::string basename_;//日志文件名公共部分
    const off_t rollSize_;//滚动日志阈值

    Thread thread_;//后端线程
    std::mutex mutex_;
    std::condition_variable cond_;

    BufferPtr currentBuffer_;  //前端当前写入的缓冲区Buffer(4Mb)
    BufferPtr nextBuffer_;//用于与currentBuffer_交换的备用Buffer(4MB)
    BufferVector buffers_;//缓冲队列
};
