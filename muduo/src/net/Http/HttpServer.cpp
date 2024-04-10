#include"Logging.h"
#include"HttpContext.h"
#include"HttpRequest.h"
#include"HttpResponse.h"
#include"HttpServer.h"

using namespace std;
using namespace std::placeholders;


//设定默认Http回调函数(404状态码并关闭连接)
void defaultHttpCallback(const HttpRequest&, HttpResponse *response)
{
    response->setStatusCode(HttpResponse::k404NotFound);
    response->setStatusMessage("Not Found");
    response->setCloseConnection(true);
}

HttpServer::HttpServer(EventLoop *loop, const InetAddress &listenAddr, const std::string &name, TcpServer::Option option)
:tcpServer_(loop, listenAddr, name, option),
httpCallback_(defaultHttpCallback)
{
    tcpServer_.setConnectionCallback(std::bind(&HttpServer::onConnection, this, std::placeholders::_1));
    tcpServer_.setMessageCallback(std::bind(&HttpServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 ));
}

void HttpServer::start()
{
    LOG_INFO <<"HttpServer[" <<tcpServer_.name().c_str() <<"] starts listening on" << tcpServer_.ipPort().c_str();
    tcpServer_.start(); 
}

//建立连接或断开连接回调函数
void HttpServer::onConnection(const TcpConnectionPtr &conn)
{
    if(conn->connected())
    {
        LOG_DEBUG << "New Connection Arrived";
    }
    else
    {
        LOG_DEBUG << "Connection Closed, name = " << conn->name();
    }
}

//可读事件回调函数(解析请求+请求回调)
void HttpServer::onMessage(const TcpConnectionPtr &conn, Buffer *buf, TimeStamp receiveTime)
{
    std::unique_ptr<HttpContext> context(new HttpContext);

    if(!context->parseRequest(buf, receiveTime))//解析请求
    {
        LOG_INFO <<"parseRequest failed!";
        conn->send("HTTP/1.1 400 Bad Request\r\n\r\n");
        conn->shutdown();
    }

    if(context->gotAll())//解析完毕
    {
        onRequest(conn, context->request());
        context->reset();
    }
}

//请求回调函数
void HttpServer::onRequest(const TcpConnectionPtr &conn, const HttpRequest &request)
{
    const string &connection = request.getHeder("Connection");//获取请求中connection头部字段值
    //判断短连接还是长连接
    bool close = ((connection == "close") || (request.version() == HttpRequest::kHttp10 && connection != "Keep-Alive") );
    HttpResponse response(close);

    httpCallback_(request, &response);//用户自定义，当请求到来时，服务端返回给客户端什么消息

    Buffer buf;
    response.appendToBuffer(&buf);//将http响应填入buf
    conn->send(&buf);//发送数据到文件描述符

    if(response.closeConnection())//短连接
    {
        LOG_DEBUG << "the server close http connection, named:" << conn->name();
        conn->shutdown();
    }
    
}



