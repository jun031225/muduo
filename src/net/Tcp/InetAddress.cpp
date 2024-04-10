#include"InetAddress.h"

#include<string.h>

//服务端
InetAddress::InetAddress(uint16_t port)
{
    ::memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = ::htons(port);//转换为网络字节序(大端序)
    addr_.sin_addr.s_addr = ::htonl(INADDR_ANY);
}

//客户端
InetAddress::InetAddress(std::string ip, uint16_t port)
{
    ::memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = ::htons(port);
    addr_.sin_addr.s_addr = ::inet_addr(ip.c_str());//点分十进制ip地址转换为二进制网络字节序
}

// TODO: 网络字节序和主机字节序的转换函数

//将网络字节序的Ip地址转换为点分十进制
std::string InetAddress::toIp() const
{
    char buf[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof(buf));//网络字节序ip地址转换为点分十进制
    return buf;
}

//将网络字节序的ip地址和端口号转换为类似"127.0.0.1: 8080"样式
std::string InetAddress::toIpPort() const
{
    char buf[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof(buf));
    size_t end = ::strlen(buf);
    uint16_t port = ::ntohs(addr_.sin_port);
    sprintf(buf + end, ":%u", port);
    return buf;
}

//将网络字节序的端口号转换为主机字节序的端口号
uint16_t InetAddress::toPort() const
{
    return ::ntohs(addr_.sin_port);
}
