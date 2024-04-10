#pragma once

#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>

//对地址信息进行了包装，是sockaddr_in的包装类
//提供IPv4网络字节序ip地址，端口号与主机字节序的相互转换

class InetAddress
{
    public:
    explicit InetAddress(uint16_t port = 0);
    explicit InetAddress(const sockaddr_in &addr) :addr_(addr){}
    InetAddress(std::string ip, uint16_t port);

    std::string toIp() const;
    std::string toIpPort() const;
    uint16_t toPort() const;

    const sockaddr_in *getSocketAddr() const {return &addr_;}
    void setSocketAddr(const sockaddr_in &addr){addr_ = addr;}

    private:

    sockaddr_in addr_;
};