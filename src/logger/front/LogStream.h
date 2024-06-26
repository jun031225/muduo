#pragma once

#include "FixedBuffer.h"

// 输出通用模版，用于将时间，文件名写入buffer(4KB)
class GeneralTemplate : noncopyable
{
public:
     const char *data_;
    int len_;

    GeneralTemplate() : data_(nullptr), len_(0) {}
    explicit GeneralTemplate(const char *data, int len) : data_(data), len_(len) {}
};


// LogStream：重载<<运算符,将数据写入buffer(4KB)
class LogStream : noncopyable
{
public:
    using SmallBuffer = FixedBuffer<kSmallBuffer>;

    void append(const char *data, int len)
    {
        buffer_.append(data, len);
    }

    const SmallBuffer& buffer() const { return buffer_; } // 获取buffer
    void resetBuffer() { buffer_.reset(); }

    // 重载运算符"<<"，以便可以像cout那样 << 任意类型
    LogStream& operator<<(short);
    LogStream& operator<<(unsigned short);
    LogStream& operator<<(int);
    LogStream& operator<<(unsigned int);
    LogStream& operator<<(long);
    LogStream& operator<<(unsigned long);
    LogStream& operator<<(long long);
    LogStream& operator<<(unsigned long long);
    LogStream& operator<<(float v);
    LogStream& operator<<(double v);
    LogStream& operator<<(char c);
    LogStream& operator<<(const void *p);
    LogStream& operator<<(const char *str);
    LogStream& operator<<(const unsigned char *str);
    LogStream& operator<<(const std::string &str);
    LogStream& operator<<(const SmallBuffer &buf);
    LogStream& operator<<(const GeneralTemplate &g); // 相当于(const char*, int)的重载
private:
    static const int maxNumericSize = 48; // 数字（整数或者浮点数）转换为字符串后最大的长度
    SmallBuffer buffer_;                  // 4KB，重载的所有运算符都是在向buffer中写数据，

    template <typename T>
    void formatInteger(T); // 将整数处理成字符串并添加到buffer_中
};