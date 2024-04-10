#pragma once

#include"noncopyable.h"
#include"TimeStamp.h"
#include<map>


//Http请求

class HttpRequest
{
    public:
    enum Method{Kinvalid, kGet, kPost, kHead, kPut, kDelete};
    enum Version{kUnknown, kHttp10, kHttp11};

    HttpRequest() : method_(Kinvalid), version_(kUnknown){}

    Version version() const {return version_;}
    Method method() const {return method_;}
    const std::string& path() const {return path_;}
    const std::string &query() const {return query_;}
    TimeStamp receiveTime() const {return receiveTime_;}
    const std::map<std::string, std::string>& headers() const {return headers_;}//获取请求头部列表
    std::string getHeder(const std::string &field) const //获取请求头部值
    {
        std::string result;
        auto it = headers_.find(field);
        if(it != headers_.end())
        {
            result = it->second;
        }
        return result;
    }


    //设定版本号
    void setVersion(Version v){version_ = v;}
    //设定请求方法
    bool setMethod(const char *start, const char *end)
    {
        std::string method(start,end);
        if(method == "GET") {method_ = kGet;}
        else if(method == "POST") {method_ = kPost;}
        else if(method == "HEAD") {method_ = kHead;}
        else if(method == "PUT") {method_ = kPut;}
        else if( method == "DELETE" ) { method_ = kDelete; }
        else { method_ = Kinvalid; }
        return method_ !=Kinvalid;
    }
    //设定请求路径
    void setPath(const char *start, const char *end)
    {
        path_.assign(start, end);
    }
    //设定询问参数
    void setQuery(const char *start, const char *end)
    {
        query_.assign(start, end);
    }
    //设定请求时间
    void setReceiveTime(TimeStamp t){receiveTime_ = t;}

    //添加请求头部到请求头部列表
    void addHeader(const char *start, const char *colon, const char *end)
    {
        std::string field(start, colon);//头部字段名
        ++colon;//跳过冒号
        while(colon < end && isspace(*colon))//跳过空白字段
        {
            ++colon;
        }

        std::string value(colon, end);//头部字段值
        while(!value.empty() && isspace(value[value.size() - 1]))//去掉后面的空白
        {
            value.resize(value.size() - 1);
        }
        headers_[field] = value;
    }

    const char* methodString() const
    {
        const char *result = "UNKNOWN";
        switch(method_)
        {
            case kGet : result = "GET";break;
            case kPost : result = "POST";break;
            case kHead : result = "HEAD";break;
            case kPut : result = "PUT";break;
            case kDelete : result = "DELETE";break;
            default : break;
        }
        return  result;
    }

    //交换请求消息
    void swap(HttpRequest &rhs)
    {
        std::swap(method_, rhs.method_);
        std::swap(version_, rhs.version_);
        path_.swap(rhs.path_);
        query_.swap(rhs.query_);
        std::swap(receiveTime_, rhs.receiveTime_);
        headers_.swap(rhs.headers_);
    }
    private:
    Method method_;//请求方法
    Version version_;//版本号
    std::string path_;//请求路径
    std::string query_;//询问参数
    TimeStamp receiveTime_;//请求时间
    std::map<std::string, std::string> headers_;//请求头部列表
};