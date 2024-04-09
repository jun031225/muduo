#pragma once

#include "noncopyable.h"

#include <thread>
#include <functional>
#include <memory>
#include <string>
#include <atomic>

// 封装了线程的创建、启动、等待和销毁过程，提供了简单的接口供用户使用,方便对线程进行管理
// 允许用户指定线程的名称，并提供默认名称设置函数。
// 通过静态成员变量 numCreated_ 统计已经创建的 Thread 实例数量。
class Thread
{
public:
    using ThreadFunc = std::function<void()>;

    explicit Thread(ThreadFunc func, const std::string &name);
    ~Thread();

    void start(); // 开启线程
    void join();  // 等待线程

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const std::string &name() const { return name_; }
    static int numCreated() { return numCreated_; }

private:
    void setDefaultName(); // 设置线程名

    bool started_; // 线程是否已经启动
    bool joined_;
    std::shared_ptr<std::thread> thread_;
    pid_t tid_;                             // 线程id
    ThreadFunc func_;                       // 线程运行函数
    std::string name_;                      // 线程名
    static std::atomic_int32_t numCreated_; // 线程索引
};