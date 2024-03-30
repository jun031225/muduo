#include"AsyncLogging.h"
#include"TimeStamp.h"

#include<stdio.h>

AsyncLogging::AsyncLogging(const std::string &basename, off_t rollSize, int flushInterval)
:flushInterval_(flushInterval),
running_(false),
basename_(basename),
rollSize_(rollSize),
thread_(std::bind(&AsyncLogging::threadFunc, this), "Logging"),//将线程函数绑定到当前对象
mutex_(),
cond_(),
currentBuffer_(new Buffer),
nextBuffer_(new Buffer),
buffers_()
{
    //清空缓冲区(4MB),设置缓冲区队列容量为16个元素
    currentBuffer_->bzero();
    nextBuffer_->bzero();
    buffers_.reserve(16);
}

//前端将完整的4KB的日志填入currentBuffer(4MB)
void::AsyncLogging::append(const char *logline, int len)
{
    //加锁避免多个线程同时对currentBuffer写入日志
    std::lock_guard<std::mutex> lock(mutex_);
    if(currentBuffer_->avail() > len)
    {
        currentBuffer_->FixedBuffer::append(logline, len);
    }
}