#pragma once

#include<string>
#include<functional>
#include<memory>
#include<vector>

class EventLoop;
class EventLoopThread;

//在服务器程序中管理多个事件循环线程，通过轮询的方式分发连接给子 Reactor 来实现负载均衡。
class EventLoopThreadPool
{
    public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;
    EventLoopThreadPool(EventLoop *baseloop, const std::string &nameArg);
    ~EventLoopThreadPool();

    void setThreadNum(int numThreads){numThreads_ = numThreads;}

    //启动线程池
    void start(const ThreadInitCallback &cb = ThreadInitCallback());

    // 主Reactor将新接受的连接分发给子Reactor时，通过轮询的方式获取应该分发给哪个子Reactor（EventLoop）
    EventLoop *getNextLoop();//获取子Reactor(事件循环)

    std::vector<EventLoop*> getAllLoops();

    bool started() const {return started_;}//线程池是否启动
    const std::string name() const {return name_;}//获取线程池名称

    private:
    EventLoop *baseloop_; // 主线程（主Reactor）对应的EventLoop
    std::string name_;
    bool started_;//是否已经开启线程池
    int numThreads_;//线程池中线程数量
    size_t next_;//下一个要分配的事件循环的索引
    std::vector<std::unique_ptr<EventLoopThread>> threads_;//线程池对象(时间循环的线程)
    std::vector<EventLoop*> loops_;//事件循环(子Reactor)的集合
};