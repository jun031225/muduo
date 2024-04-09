#pragma once

#include<map>
#include<string>

class Buffer;

class HttpResponse
{
    public:
    //状态码
    enum HttpStatusCode
    {
        KUnknown,
        k200Ok = 200,
        k301MovedPermanently = 301,//资源已被移动
        k400BadRequest = 400,//客户端错误(参数无效)
        k404NotFound = 404,//客户端错误(资源不存在)
        k403Forbidden = 403,//客户端错误(服务端拒绝执行请求)
    };

    explicit HttpResponse(bool close):statusCode_(KUnknown),closeConnection_(close){}

    void setStatusCode(HttpStatusCode code){statusCode_ = code;}//设定状态码
    void setStatusMessage(const std::string &message){statusMessage_ = message;}//设定状态码描述
    void setCloseConnection(bool on){closeConnection_ = on;}
    bool closeConnection() const {return closeConnection_;}
    void setContentType(const std::string &contentType){addHeader("Content-Type", contentType);}//添加头部字段Content-type
    void setBody(const std::string &body){body_ = body;}//设定响应体
    void addHeader(const std::string &key, const std::string &value){headers_[key] = value;}//添加头部
    void appendToBuffer(Buffer *output) const;

    private:
    std::map<std::string, std::string> headers_;//响应头部列表
    HttpStatusCode statusCode_;//状态码
    std::string statusMessage_;//状态码描述
    bool closeConnection_;//长连接还是短连接
    std::string body_;//响应体
};