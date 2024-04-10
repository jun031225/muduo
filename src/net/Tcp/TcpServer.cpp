#include"TcpServer.h"

// 检查传入的 baseLoop 指针是否有意义
static EventLoop* CheckLoopNotNull(EventLoop *loop)
{
    if(loop == nullptr)
    {
        LOG_FATAL << "mainLoop is null!";
    }
    return loop;
}

TcpServer::TcpServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &nameArg, Option option)
:loop_(CheckLoopNotNull(loop)),
ipPort_(listenAddr.toIpPort()),
name_(nameArg),
acceptor_(new Acceptor(loop, listenAddr, option == kReusePort)),
threadPool_(new EventLoopThreadPool(loop, name_)),
connectionCallback_(defaultConnectionCallback),
messageCallback_(defaultMessageCallback),
writeCompleteCallback_(),
threadInitCallback_(),
started_(0),
nextConnId_(1)
{
    // 当有新用户连接时，Acceptor类中绑定的acceptChannel_会有读事件发生执行handleRead()调用TcpServer::newConnection回调
    acceptor_->setNewConnectionCallback(std::bind
    (&TcpServer::newConnection, this, std::placeholders::_1, std::placeholders::_2));
}

TcpServer::~TcpServer()
{
    for(auto &item : connections_)
    {
        TcpConnectionPtr conn(item.second);
        // 把原始的智能指针复位 让栈空间的TcpConnectionPtr conn指向该对象 当conn出了其作用域 即可释放智能指针指向的对象
        item.second.reset();
        conn->getLoop()->runInLoop(std::bind(&TcpConnection::connectDestroyed, conn));//销毁连接
    }
}

//设置subReactor数量
void TcpServer::setThreadNum(int numThreads)
{
    threadPool_->setThreadNum(numThreads);
}

void TcpServer::start()
{
    if(started_++ == 0)
    {
        //启动线程池
        threadPool_->start(threadInitCallback_);
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
    }
}


// 有一个新用户连接，acceptor会执行这个回调操作，负责将mainLoop接收到的请求连接(acceptChannel_会有读事件发生)通过回调轮询分发给subLoop去处理
void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr)
{
    //轮询
    EventLoop *subLoop = threadPool_->getNextLoop();
    char buf[64]={0};
    snprintf(buf, sizeof(buf), "-%s#%d", ipPort_.c_str(), nextConnId_);
    ++nextConnId_;

    //新连接名字
    std::string connName = name_ + buf;

    LOG_INFO << "TcpServer::newConnection [" << name_.c_str() <<
     "] - new connection [" <<connName.c_str() <<"] from " << peerAddr.toIpPort().c_str();

     sockaddr_in local;
     ::memset(&local, 0, sizeof(local));
     socklen_t addrlen = sizeof(local);
     if(::getsockname(sockfd, (sockaddr*)&local, &addrlen) < 0)//获取本地地址信息
     {
        LOG_ERROR << "socket::getLocalAddr() failed";
     }

    //构造Tcp连接
     InetAddress localAddr(local);
     TcpConnectionPtr conn(new TcpConnection(subLoop, connName, sockfd, localAddr, peerAddr));
     connections_[connName] = conn;

    //设置连接的回调函数
     conn->setConnectionCallback(connectionCallback_);
     conn->setMessageCallback(messageCallback_);
     conn->setWriteCompleteCallback(writeCompleteCallback_);
     conn->setCloseCallback(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));

     subLoop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr &conn)
{
    loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}



void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn)
{
    LOG_INFO <<"TcpServer::removeConnectionInLoop [" <<name_.c_str() << "] - connection" << conn->name().c_str();

    connections_.erase(conn->name());
    EventLoop *subLoop = conn->getLoop();
    subLoop->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
}