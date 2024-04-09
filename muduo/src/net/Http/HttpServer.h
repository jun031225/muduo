#pragma once 

#include"TcpServer.h"

class  HttpRequest;
class HttpResponse;

class HttpServer: noncopyable
{
    public:

    using HttpCallback = std::function<void(const HttpRequest&, HttpResponse*)>;

    HttpServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &name, TcpServer::Option option = TcpServer::kNoReusePort);

    EventLoop *getLoop() const{return tcpServer_.getLoop();}//获取所在循环

    //设定http请求到来时的回调函数(自定义)
    void setHttpCallback(const HttpCallback &cb)
    {
        httpCallback_ = cb;
    }

    //设定事件循环线程数量
    void setThreadNum(int threadNum)
    {
        tcpServer_.setThreadNum(threadNum);
    }
    
    void start();
    private:
    void onConnection(const TcpConnectionPtr &conn);
    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, TimeStamp receiveTime);
    void onRequest(const TcpConnectionPtr &, const HttpRequest &);

    TcpServer tcpServer_;
    HttpCallback httpCallback_;//http请求到来时的回调函数   
};