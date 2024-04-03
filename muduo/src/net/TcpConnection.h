#pragma once

#include "noncopyable.h"
#include "Callback.h"
#include "Buffer.h"
#include "TimeStamp.h"
#include "InetAddress.h"

#include <atomic>

class Channel;
class EventLoop;
class Socket;
//通过使用 shared_from_this()，您可以避免创建新的共享指针，并确保维护现有的共享所有权。
class TcpConnection : noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop *loop, const std::string &nameArg,
                  int sockfd, const InetAddress &localAddr, const InetAddress &peerAddr);
    ~TcpConnection();

    EventLoop *getLoop() const { return loop_; }
    const std::string &name() const { return name_; }
    const InetAddress &localAddress() const { return localAddr_; }
    const InetAddress &peerAddress() const { return peerAddr_; }

    bool connected() const { return state_ == kConnected; } // 是否已连接

    // 发送数据
    void send(const std::string &buf);
    void send(Buffer *buf);

    // 关闭连接
    void shutdown();

    // 用户自定义的回调函数
    void setConnectionCallback(const ConnectionCallback &cb) { connectionCallback_ = cb; }
    void setMessageCallback(const MessageCallback &cb) { messageCallback_ = cb; }
    void setWriteCompleteCallback(const WriteCompleteCallback &cb) { writeCompleteCallback_ = cb; }
    void setCloseCallback(const CloseCallback &cb) { closeCallback_ = cb; }
    void setHighWaterMarkCallback(const HighWaterMarkCallback &cb, size_t highWaterMark)
    {
        highWaterMarkCallback_ = cb;
        highWaterMark_ = highWaterMark;
    }

    // 供TcpServer调用
    void connectEstablished(); // 连接建立
    void connectDestroyed();   // 连接销毁

private:
    // 连接状态
    enum StateE
    {
        kDisconnected, // 已经断开连接
        kConnecting,   // 正在连接
        kConnected,    // 已连接
        kDisconnecting // 正在断开连接
    };

    void setState(StateE state) { state_ = state; } // 设置连接状态

    // fd上有事件发生时所调用的回调函数
    void handleRead(TimeStamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();

    // 在自己所属的loop中发送数据
    void sendInLoop(const void *message, size_t len);
    void sendInLoop(const std::string &message);
    // 在自己所属的loop中关闭连接
    void shutdownInLoop();

    EventLoop *loop_; // 属于哪个subLoop(单线程则为baseLoop)
    const std::string name_;
    std::atomic_int state_; // 连接状态
    bool reading_;

    std::unique_ptr<Socket> socket_;   // 对fd的封装
    std::unique_ptr<Channel> channel_; // fd对应的channel

    const InetAddress localAddr_; // 本服务器地址
    const InetAddress peerAddr_;  // 对端地址

    /**
     * 用户自定义的这些事件的处理函数，然后传递给 TcpServer
     * TcpServer 再在创建 TcpConnection 对象时候设置这些回调函数到TcpConnection中
     */
    ConnectionCallback connectionCallback_;       // 有新连接时的回调函数
    MessageCallback messageCallback_;             // 有读写消息时的回调函数
    WriteCompleteCallback writeCompleteCallback_; // 消息发送完成以后的回调函数
    CloseCallback closeCallback_;                 // 客户端关闭连接的回调函数
    // 是在Buffer存储的待发送或者待读取处理的数据超过我们设定的上线后执行的回调
    HighWaterMarkCallback highWaterMarkCallback_;

    ssize_t highWaterMark_; // 水位

    Buffer inputBuffer_;  // 读取数据的缓冲区
    Buffer outputBuffer_; // 发送数据的缓冲区
};
