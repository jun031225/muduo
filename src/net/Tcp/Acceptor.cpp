#include "Acceptor.h"
#include "Logging.h"
#include "InetAddress.h"

#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static int createNonblocking()
{
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP); // 创建套接字
    if (sockfd < 0)
    {
        LOG_FATAL << "listen socket create err" << errno;
    }
    return sockfd;
}

Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport)
    : loop_(loop),
      acceptSocket_(createNonblocking()),
      acceptChannel_(loop, acceptSocket_.fd()),
      listenning_(false),
      idlefd_(::open("/dev/null", O_RDONLY | O_CLOEXEC))
{
    LOG_DEBUG << "Acceptor create nonblocking socket, [fd =" << acceptChannel_.fd() << "]";
    acceptSocket_.setReuseAddr(reuseport);
    acceptSocket_.setReusePort(true);
    acceptSocket_.bindAddress(listenAddr);

    // 为acceptChannel_的fd绑定可读事件，当有新连接到来时，acceptChannel_的fd可读
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

Acceptor:: ~Acceptor()
{
    acceptChannel_.delAll();
    acceptChannel_.remove();
    ::close(idlefd_);
}

void Acceptor::listen()
{
    listenning_ = true;
    acceptSocket_.listen();
    acceptChannel_.addReading();//注册读事件
}

// listenfd有事件发生了，就是有新用户连接了
void Acceptor::handleRead()
{
    InetAddress peerAddr;
    int connfd = acceptSocket_.accept(&peerAddr);//接受连接
    if(connfd >= 0)//有连接到来
    {
        if(newConnectionCallback_)
        {
            newConnectionCallback_(connfd, peerAddr);
        }
        else
        {
            LOG_DEBUG << "no newConnectionCallback() function";
            ::close(connfd);
        }
    }
    else
    {
        LOG_ERROR << "Accept() failed";
        // 当前进程的fd已经用完了
        // 可以调整单个服务器的fd上限
        // 也可以分布式部署
        if(errno == EMFILE)
        {
            LOG_INFO <<"sockfd reached limit";
            ::close(idlefd_);
            idlefd_ = ::accept(acceptSocket_.fd(), NULL, NULL);
            ::close(idlefd_);
            idlefd_ = ::open("/dev/null", O_RDONLY | O_CLOEXEC);
        }
    }
}

