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

AsyncLogging::~AsyncLogging()
    {
        if (running_)
        {
            stop();
        }
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

    //currentBuffer写满
    else
    {
        buffers_.push_back(std::move(currentBuffer_));//放入缓冲队列buffers_，置空currentBuffer_

        if(nextBuffer_)
        {
            //将nextBuffer的内存区域所有权移交给currentBuffer_,nextBuffer_被置空
            currentBuffer_ = std::move(nextBuffer_);
        }
        else//nextBuffer_也不够用，重新分配缓冲区
        {
            currentBuffer_.reset(new Buffer);
            currentBuffer_->FixedBuffer::append(logline, len);
        }
        
        cond_.notify_one();
    }
}

void AsyncLogging::threadFunc()
{
    LogFile output(basename_,rollSize_, false);

    //后端缓冲区，用于和前端的currentBuffer和nextBuffer进行交换
    BufferPtr newBuffer1(new Buffer);
    BufferPtr newBuffer2(new Buffer);
    newBuffer1->bzero();
    newBuffer2->bzero();

    BufferVector buffersToWrites;//待写缓冲队列
    buffersToWrites.reserve(16);

    while(running_)
    {
        //主要负责前后端缓冲区的转移，缓冲队列的交换
        {
            std::unique_lock<std::mutex> lock(mutex_);
            if(buffers_.empty())
            {
                cond_.wait_for(lock, std::chrono::seconds(3));//等待三秒也会解除阻塞
            }

            buffers_.push_back(std::move(currentBuffer_));//currentBuffer放入缓冲队列
            currentBuffer_ = std::move(newBuffer1);//移动缓存区
            if(!nextBuffer_)
            {
                nextBuffer_ = std::move(newBuffer2);//移动缓冲区
            }
             buffersToWrites.swap(buffers_);//交换缓冲队列(待写缓冲队列和已满缓冲队列)
        }

        //将待写缓冲队列的日志写入日志文件
        for(const auto& buffer : buffersToWrites)
        {
            output.append(buffer->data(), buffer->length());
        }

        //只保留两个缓冲区用于后端两个空闲的缓冲区
        if(buffersToWrites.size() > 2)
        {
            buffersToWrites.resize(2);
        }
        if(!newBuffer1)
        {
            newBuffer1 = std::move(buffersToWrites.back());
            buffersToWrites.pop_back();
            newBuffer1->reset();
        }
        if(!newBuffer2)
        {
            newBuffer2 = std::move(buffersToWrites.back());
            buffersToWrites.pop_back();
            newBuffer2->reset();
        }

        buffersToWrites.clear();//清空后端待写缓冲区队列
        output.flush();//刷新文件缓冲区
    }
    output.flush();
}