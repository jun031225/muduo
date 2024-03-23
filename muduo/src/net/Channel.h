#pragma once

#include "TimeStamp.h"
#include "logging.h"
#include "noncopyable.h"

#include <memory>
#include <functional>

class EventLoop;

// Channel类就将fd感兴趣的事件和实际发生的事件封装在一起，同时保存了事件发生时对应的回调函数（注意，一个Channel自始至终只负责一个fd）

class Channel : noncopyable
{
public:
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(TimeStamp)>;

    Channel(EventLoop *loop, int fd);
    ~Channel();

    // 返回文件描述符，事件
    int fd() const { return fd_; }
    int events() const { return events_; }
    int revents() const { return revents_; }

    EventLoop *ownerLoop() { return loop_; }    // 返回Channel所属的EventLoop
    void set_revents(int re) { revents_ = re; } // 设置poller返回的实际发生的事件

    // 返回fd当前的事件状态(是否注册可读，可写事件，空事件)
    bool isReading() const { return events_ & kReadEvent; }
    bool isWriting() const { return events_ & kWriteEvent; }
    bool isNoneEvent() const { return events_ == kNoneEvent; }

    // 返回/设置fd在epoller中的状态
    /**
     * for EPoller
     * const int kNew = -1;     // fd还未被Epoller监视
     * const int kAdded = 1;    // fd正被Epoller监视中
     * const int kDeleted = 2;  // fd被从Epoller中移除
     */
    int index() const { return index_; }
    void set_index(int idx) { index_ = idx; }

    // 设置回调函数
    void setReadCallback(ReadEventCallback cb) { readCallback_ = std::move(cb); }
    void serWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb) { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }

    void handleEvent(TimeStamp receiveTime); // fd得到epoller通知，处理事件回调函数

    // 将TcpConnection的共享指针和Channel的成员弱指针绑定tie_，便于在Channel在处理事件时，
    // 防止TcpConnection已经被析构了（即连接已经关闭了）
    void tie(const std::shared_ptr<void> &);

    // 将fd与event注册到事件监听器或从中移除，本质调用epoll_ctl
    void addReading()
    {
        events_ |= kReadEvent;
        update();
    }
    void delReading()
    {
        events_ &= ~kReadEvent;
        update();
    }
    void addWriting()
    {
        events_ |= kWriteEvent;
        update();
    }
    void delWriting()
    {
        events_ &= ~kWriteEvent;
        update();
    }
    void delAll()
    {
        events_ &= kNoneEvent;
        update();
    }

    void remove(); // 从epoller中移除，即让epoller停止关注fd感兴趣的事件
private:
    EventLoop *loop_; // 所属的EventLoop
    const int fd_;    // 管理的文件描述符
    int events_;      // 感兴趣的事件
    int revents_;     // 实际发生的事件
    int index_;       // 在epoller注册的状态(kNew,kAdded,kDeleted-未监视，被监视，已移除)

    std::weak_ptr<void> tis_; // 弱指针指向TcpConnection(必要时升级为shared_ptr多一份引用计数，避免用户误删)
    bool tied_;               // 标志此 Channel 是否被调用过 Channel::tie 方法
    // 保存事件发生时的回调函数
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;

    // 感兴趣的事件类型
    /**
     * const int Channel::kNoneEvent = 0;
     * const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
     * const int Channel::kWriteEvent = EPOLLOUT;
     */
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    void update(); // 调用epoll_ctl
    void handleEventWithGuard(TimeStamp receiveTime);
};
