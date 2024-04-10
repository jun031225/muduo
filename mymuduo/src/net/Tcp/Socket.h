#pragma once

#include "noncopyable.h"

class InetAddress;

/**
* socket fd 包装类
*　RAII机制管理socket fd: 对close socket fd负责, 但不包括open/create.
* 监听socket, 常用于server socket.
*/
class Socket : noncopyable
{
public:
    explicit Socket(int sockfd) : sockfd_(sockfd) {}
    ~Socket();

    int fd() const{return sockfd_;}
    void bindAddress( const  InetAddress &localaddr);//绑定sockfd与本地ip地址，端口号
    void listen();//监听连接
    int accept(InetAddress *peeraddr);//接受连接请求

    void shutdownWrites();//关闭连接写

    void setTcpNoDelay(bool on);//设置TCP_NODELAY
    void setReuseAddr(bool on);//设置SO_REUSEADDR
    void setReusePort(bool on);//设置SO_REUSEPORT
    void setKeepAlive(bool on);//设置SO_KEEPALIVE

private:
    const int sockfd_;
};