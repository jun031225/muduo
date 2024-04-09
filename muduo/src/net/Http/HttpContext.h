#pragma once

#include"HttpRequest.h"

class Buffer;

//解析从buf中传来的http请求
class HttpContext
{
    public:
    enum HttpRequestParseState//解析状态
    {
        kExpectRequestLine,
        kExpectHeaders,//解析请求头部行
        kExpectBody,//解析请求体状态
        kGotAll,//解析完毕状态
    };

    HttpContext():state_(kExpectRequestLine){}

    bool parseRequest(Buffer *buf, TimeStamp recevieeTime);//解析请求行

    bool gotAll() const {return state_ ==kGotAll;}

    void reset()
    {
        state_ = kExpectRequestLine;
        HttpRequest dummy;
        request_.swap(dummy);
    }

    const HttpRequest request()const{return request_;}
    HttpRequest& request(){return request_;}

    private:
    bool processRequestLine(const char *begin, const char *end);
    HttpRequestParseState state_;//解析状态
    HttpRequest request_;//Http请求
};