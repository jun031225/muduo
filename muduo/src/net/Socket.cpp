#include "Socket.h"
#include "InetAddress.h"
#include "Logging.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <unistd.h>

Socket::~Socket()
{
    ::close(sockfd_);
}

//绑定sockfd与本地地址
void Socket::bindAddress(const InetAddress &localaddr)
{
    if (::bind(sockfd_, (sockaddr *)localaddr.getSocketAddr(), sizeof(sockaddr_in)) != 0)
    {
        LOG_FATAL << "bind sockfd:" << sockfd_ << "fail";
    }
}

//监听连接
void Socket::listen()
{
    // 监听队列长度设置为1024
    if (::listen(sockfd_, 1024) != 0)
    {
        LOG_FATAL << "listen sockfd:" << sockfd_ << "fail";
    }
}

//接受连接，返回连接的文件描述符
int Socket::accept(InetAddress *peeradr)
{
    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    ::memset(&addr, 0, sizeof(addr));

    // SOCK_NONBLOCK表示把connfd设置成非阻塞。SOCK_CLOEXEC表示用fork调用创建子进程时在子进程中关闭该socket
    int connfd = ::accept4(sockfd_, (sockaddr *)&addr, &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if(connfd >= 0)
    {
        peeradr->setSocketAddr(addr);
    }
    else
    {
        LOG_ERROR << "accept4() failed";
    }
    return connfd;
}

//关闭sockfd_的写端，关闭后不可以继续写数据，但是依然可以接受数据
void Socket::shutdownWrites()
{
    if(::shutdown(sockfd_, SHUT_WR) < 0)
    {
        LOG_ERROR << "shutdownWrites error";
    }
}

/**
 * TCP_NODELAY禁用Nagle算法，参考：https://zhuanlan.zhihu.com/p/80104656
 * Nagle算法的作用是减少小包的数量，原理是：当要发送的数据小于MSS时，数据就先不发送，而是先积累起来
 * Nagle算法优点：有效减少了小包数量，减小了网络负担
 * 缺点：由于要积累数据，会带来一定延迟，对于实时性要求较高的场景最好禁用Nagle算法
*/
void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval)); 
}

// 设置地址复用，其实就是可以使用处于Time-wait的地址
void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)); 
}

// 通过改变内核信息，多个进程可以绑定同一个地址。通俗就是多个服务的ip+port是一样
void Socket::setReusePort(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)); 
}

// SO_KEEPALIVE作用：如果通信两端超过2个小时没有交换数据，那么开启keep-alive的一端会自动发一个keep-alive包给对端。
void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval)); 
}