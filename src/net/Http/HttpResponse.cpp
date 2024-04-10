#include"HttpResponse.h"
#include"Buffer.h"

#include<stdio.h>
#include<string.h>
#include<iostream>

//将Http响应填入buffer
void HttpResponse::appendToBuffer(Buffer *output) const
{
    char buf[32];
    snprintf(buf, sizeof(buf), "HTTP/1.1 %d", statusCode_);
    //填入响应状态行到buffer
    output->append(buf);
    output->append(statusMessage_.data());
    output->append("\r\n");

    if(closeConnection_)//连接关闭
    {
        output->append("Connection: close\r\n");
    }
    else//填入响应头部字段content-length和connection
    {
        snprintf(buf, sizeof(buf), "Content-length :%zd\r\n", body_.size());
        output->append(buf);
        output->append("Connection: Keep-Alive\r\n");
    }

    for(const auto &header : headers_)//填入其余响应头部字段到buffer
    {
        output->append(header.first);
        output->append(": ");
        output->append(header.second);
        output->append("\r\n"); 
    }
    output->append("\r\n");
    output->append(body_);//填入响应体
}