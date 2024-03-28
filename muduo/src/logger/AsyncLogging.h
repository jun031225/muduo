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

private:
    using Buffer = FixedBuffer<kLargeBUffer>; // 4MB

    // BufferVector存储独占指针的目的是：从BufferVector中弹出元素（Buffer）后会自动析构
    using BufferVector = std::vector<std::unique_ptr<Buffer>>;
    using BufferPtr = BufferVector::value_type;

    void threadFunc();

    const int flushInterval_;
    std::atomic<bool> running_;
    const std::string basename_;
    const off_t rollSize_;
    Thread thread_;
    
};
