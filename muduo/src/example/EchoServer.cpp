
#include"Logging.h"
#include"LogFile.h"
#include"TcpServer.h"

#include<string>

class EchoServer
{
    public:
    EchoServer(EventLoop *loop, const InetAddress &addr, const std::string &name)
    :loop_(loop),
    TcpServer_(loop, addr, name)
    {
        //注册回调函数  
        TcpServer_.setConnectionCallback(std::bind(&EchoServer::onConnection, this, std::placeholders::_1));
        TcpServer_.setMessageCallback(std::bind(&EchoServer::onMessge, this, std::placeholders::_1,std::placeholders::_2, std::placeholders::_3));
        //设定subloop数量
        TcpServer_.setThreadNum(3);
    }

    void start()
    {
        TcpServer_.start();
    }
    private:
    //连接建立或断开的回调函数
    void onConnection(const TcpConnectionPtr &conn)
    {
        if(conn->connected())
        {
            LOG_INFO << "Connection UP : " << conn->peerAddress().toIpPort().c_str();
        }
        else
        {
            LOG_INFO << "Connection DOWN : " << conn->peerAddress().toIpPort().c_str();
        }
    }
    //可读事件回调
    void onMessge(const TcpConnectionPtr &conn, Buffer *buf, TimeStamp time)
    {
        std::string msg = buf->retrieveAllAsString();
        conn->send(msg);
    }

    void dummyOutput(const char *msg, int len)
    {
        if(g_logFile)
        {
            g_logFile->append(msg, len);
        }
    }

    EventLoop *loop_;
    TcpServer TcpServer_;
    std::unique_ptr<LogFile> g_logFile;
};

int main()
{
    EventLoop loop;
    InetAddress addr(8080);
    EchoServer server (&loop, addr, "EchoServer");
    server.start();
    loop.loop();
    return 0;
}