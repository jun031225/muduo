#pragma once

#include"noncopyable.h"
#include"Socket.h"
#include"Channel.h"

class EventLoop;
class InetAddress;

//该类运行在主线程，主要负责监听并接收连接，接收的连接分发给其他的子Reactor（子线程）

class Acceptor
{
    public:
    using NewConnectionCallback = std::function<void(int sockfd, const InetAddress)>;
    Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback &cb)
    {
        newConnectionCallback_ = cb;
    }

    bool listenning() const {return listenning_;}
    void listen();

    private:
    void handleRead();

    EventLoop *loop_;//mainLoop
    Socket acceptSocket_;//监听套接字
    Channel acceptChannel_;//
    NewConnectionCallback newConnectionCallback_;
    bool listenning_;//是否正在监听
    int idlefd_;// 防止连接fd数量超过上限，用于占位的fd
};