#include "TcpConnection.h"
#include "Logging.h"
#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"

#include <functional>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

// 默认连接回调函数
void defaultConnectionCallback(const TcpConnectionPtr &conn)
{
    LOG_TRACE << conn->localAddress().toIpPort() << " -> "
              << conn->peerAddress().toIpPort() << " is "
              << (conn->connected() ? "UP" : "DOWN");
}

// 默认读写消息回调函数
void defaultMessageCallback(const TcpConnectionPtr &, Buffer *buf, TimeStamp)
{
    LOG_TRACE << "receive" << buf->readableBytes() << " bytes: " << buf->retrieveAllAsString();
}

// 检查循环是否为空
static EventLoop *CheckLoopNotNull(EventLoop *loop)
{
    if (loop == nullptr)
    {
        LOG_FATAL << "mainLoop is null!";
    }
    return loop;
}

TcpConnection::TcpConnection(EventLoop *loop, const std::string &nameArg,
                             int sockfd, const InetAddress &localAddr, const InetAddress &peerAddr)
    : loop_(CheckLoopNotNull(loop)),
      name_(nameArg),
      state_(kDisconnecting),
      reading_(true),
      socket_(new Socket(sockfd)),
      channel_(new Channel(loop, sockfd)),
      localAddr_(localAddr),
      peerAddr_(peerAddr),
      highWaterMark_(64 * 1024 * 1024) // 64MB
{
    // 绑定channel_各个事件发生时要执行的回调函数
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));

    LOG_INFO << "TcpConnection::creator[" << name_.c_str() << "] at fd =" << sockfd;
    socket_->setKeepAlive(true);
}

TcpConnection::~TcpConnection()
{
    LOG_INFO << "TcpConnection::deletor[" << name_.c_str() << "] at fd ="
             << channel_->fd() << "state=" << static_cast<int>(state_);
}

void TcpConnection::send(const std::string &buf)
{
    if (state_ == kConnected)
    {
        // 如果当前执行的线程就是自己所属loop绑定的线程，则可以直接发送数据
        if (loop_->isInLoopThread())
        {
            sendInLoop(buf.c_str(), buf.size());
        }
        else
        {
            loop_->runInLoop(std::bind((void(TcpConnection::*)(const std::string &)) & TcpConnection::sendInLoop, this, buf));
        }
    }
}

void TcpConnection::send(Buffer *buf)
{
    if (state_ == kConnected)
    {
        if (loop_->isInLoopThread())
        {
            sendInLoop(buf->retrieveAllAsString());
        }
        else
        {
            std::string msg = buf->retrieveAllAsString();
            loop_->runInLoop(std::bind((void(TcpConnection::*)(const std::string &)) & TcpConnection::sendInLoop, this, msg));
        }
    }
}

void TcpConnection::sendInLoop(const std::string &message)
{
    sendInLoop(message.data(), message.size());
}

/**
 * 在当前所属loop中发送数据data。发送前，先判断outputBuffer_中是否还有数据需要发送，如果没有，
 * 则直接把要发送的数据data发送出去。如果有，则把data中的数据添加到outputBuffer_中，并注册可
 * 写事件
 **/
void TcpConnection::sendInLoop(const void *data, size_t len)
{
    ssize_t nwrote = 0;      // 已发送数据长度
    size_t remaining = len;  // 剩下还未发送的数据
    bool faultError = false; // 记录是否产生错误

    if (state_ == kDisconnected) // 已经断开连接
    {
        LOG_ERROR << "disconnected, give up writing";
        return;
    }
    // 当channel_没有注册可写事件并且outputBuffer_中也没有数据要发送了，则直接*data中的数据发送出去
    // 疑问：什么时候isWriting返回false?
    // 答：刚初始化的channel和数据发送完毕的channel都是没有可写事件在epoll上的,即isWriting返回false，
    // 对于后者，见本类的handlWrite函数，发现只要把数据发送完毕，他就注销了可写事件
    if(!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
    {
        nwrote = ::write(channel_->fd(), data, len);
        if(nwrote >= 0)
        {
            remaining = len - nwrote;
            if(remaining == 0 && writeCompleteCallback_)//发送完毕
            {
                loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));//在循环中执行回调函数
            }
        }
        else//写入失败
        {
            nwrote =0;
            if(errno != EWOULDBLOCK)// 如果错误不是由于非阻塞情况下没有数据导致的
            {
                LOG_ERROR << "TcpConnection::sendInLoop";
                if(errno == EPIPE || errno == ECONNRESET)// 如果错误是由于管道断开或连接重置
                {
                    faultError = true;
                } 
            }
        }
    }

    // 如果没有发生错误且仍有剩余数据要发送
    if(!faultError && remaining > 0)
    {
        ssize_t oldLen = outputBuffer_.readableBytes();
        if(oldLen + remaining >=highWaterMark_ && oldLen < highWaterMark_ &&highWaterMark_)//发送总长度超过水位标记
        {
            loop_->queueInLoop(std::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));//在循环执行回调函数
        }
        outputBuffer_.append( (char*)data + nwrote, remaining);//将数据发送进输出缓冲区
        if(!channel_->isWriting())//注册写事件
        {
            channel_->addReading();
        }
    }
}

// 关闭连接(写端)
void TcpConnection::shutdown()
{
    if (state_ == kConnected)
    {
        setState(kDisconnecting);
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
    }
}

void TcpConnection::shutdownInLoop()
{
    if (!channel_->isWriting()) // 数据全部写完
    {
        socket_->shutdownWrites(); // 关闭写端
    }
}

// 建立连接
void TcpConnection::connectEstablished()
{
    setState(kConnected); // 设置状态为连接

    channel_->tie(shared_from_this());
    channel_->addReading();                  // 将fd的EPOLLIN读事件注册到epoller
    connectionCallback_(shared_from_this()); // 建立连接回调函数
}

// 销毁连接
void TcpConnection::connectDestroyed()
{
    if (state_ == kConnected)
    {
        setState(kDisconnected);
        channel_->delAll(); // 将channel上所有感兴趣事件删除
        connectionCallback_(shared_from_this());
    }
    channel_->remove(); // 将channel从epoller中移除
}

void TcpConnection::handleRead(TimeStamp receiveTime)
{
    int saveErrno = 0;
    ssize_t n = inputBuffer_.readFd(channel_->fd(), &saveErrno); // 从fd读取数据到inputBuffer

    if (n > 0) // 读取成功
    {
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime); // 调用用户自定义回调函数
    }
    else if (n == 0) // 对方关闭连接
    {
        handleClose(); // fd绑定的回调函数
    }
    else // 出错
    {
        errno = saveErrno;
        LOG_ERROR << "TcpConnection::handleRead() failed";
        handleError();
    }
}

void TcpConnection::handleWrite()
{
    if (channel_->isWriting())
    {
        int saveErrno = 0;
        ssize_t n = outputBuffer_.writeFd(channel_->fd(), &saveErrno); // 从outputBuffer写入数据到fd中
        if (n > 0)
        {
            outputBuffer_.reposition(n); // 复位Bufferr中readerIndex
            // 数据发送完毕
            if (outputBuffer_.readableBytes() == 0)
            {
                channel_->delWriting(); // 注销写事件，以免epoll频繁触发可写事件，导致效力低下
                if (writeCompleteCallback_)
                {
                    loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
                }
                if (state_ == kDisconnecting)
                {
                    shutdownInLoop(); // 关闭写端，保证已经发送的数据客户端还能够完整接收
                }
            }
        }
        else
        {
            LOG_ERROR << "TcpConnection::handleWrite() failed";
        }
    }
    else
    {
        LOG_ERROR << "TcpConnection fd=" << channel_->fd() << "is down, no more writing";
    }
}

void TcpConnection::handleClose()
{
    setState(kDisconnected);
    channel_->delAll(); // 移除事件
    TcpConnectionPtr connPtr(shared_from_this());
    connectionCallback_(connPtr); // 用户自定义的连接关闭回调函数
    closeCallback_(connPtr);      // 关闭连接回调
}

void TcpConnection::handleError()
{
    int optval;
    socklen_t optlen = sizeof(optval);
    int err = 0;
    if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        err = errno;
    }
    else
    {
        err = optval;
    }
    LOG_ERROR << "TcpConnection::handleError name:" << name_.c_str() << " - SO_ERROR:" << err;
}