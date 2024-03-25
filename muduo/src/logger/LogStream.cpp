#include"LogStream.h"

#include<algorithm>

//用于把数字转换为对应的字符
static const char digits[] = {'9', '8', '7', '6', '5', '4', '3', '2', '1', '0',
'1', '2', '3', '4', '5', '6', '7', '8', '9'};

//用于打印16进制的指针类型
const char digitsHex[] = "0123456789ABCDEF";

//十进制整数转换为16进制并返回长度(用于指针类型)
size_t convertHex(char buf[], uintptr_t value)
{
    uintptr_t i = value;//保证不会丢失精度
    char *p = buf;

    do
    {
        int lsd = static_cast<int>(i % 16);
        i /= 16;
        *p++ = digitsHex[lsd];
    }while(i != 0);

    *p = '\0';
    std::reverse(buf, p);

    return p - buf;
}

//整型（10进制）处理成字符串并添加到buffer_中
//从末尾开始，对待转换的整型由十进制逐位转换为char类型，然后填入buffer_
template<typename T>
void LogStream::formatInteger(T num)
{
    if(buffer_.avail() >= maxNumericSize)
    {
        char *start =buffer_.current();
        char *cur = start;
        const char *zero = digits + 9;
        bool negative = (num < 0);//是否为负数

        do
        {
            int remainder = static_cast<int>(num % 10);
            *(cur++) = zero[remainder];
            num = num /10;
        }while(num != 0);

        if(negative) //负数添加负号
        {
            *(cur++) = '-';
        }

        std::reverse(start,cur);
        buffer_.FixedBuffer::update(static_cast<int>(cur - start));//更新cur_(当前写的位置)
    }
}


//重载运算符"<<"

//对于short,unsigned short转换成int类型处理
LogStream& LogStream::operator<<(short v)
{
  *this << static_cast<int>(v);
  return *this;
}

LogStream& LogStream::operator<<(unsigned short v)
{
    *this << static_cast<unsigned int>(v);
    return *this;
}

//对于(unsigned)int,(unsigned)long,(unsigned)long long调用formatInteger转换为字符串并填入buffer_
LogStream& LogStream::operator<<(int v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned int v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(long v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(long long v)
{
    formatInteger(v);
    return *this;
}

LogStream& LogStream::operator<<(unsigned long long v)
{
    formatInteger(v);
    return *this;
}

//对于float转换为double进行处理
LogStream& LogStream::operator<<(float v) 
{
    *this << static_cast<double>(v);
    return *this;
}

//对于double，直接使用库函数snprintf转换为const char*，填入buffer_
LogStream& LogStream::operator<<(double v)
{
    if(buffer_.avail() >= maxNumericSize)
    {
        int len = snprintf(buffer_.current(), maxNumericSize, "%.12g", v);
        buffer_.update(len);
    }
    return *this;
}

//对于char类型直接填入buffer_
LogStream& LogStream::operator<<(char c)
{
    buffer_.append(&c, 1);
    return *this;
}

//输出指针的值
LogStream& LogStream::operator<<(const void *p)
{
    uintptr_t v = reinterpret_cast<uintptr_t>(p);//uintptr_t地址数与位数相同，便于不同平台使用
    if(buffer_.avail() >= maxNumericSize)
    {
        char *buf = buffer_.current();
        buf[0] = '0';
        buf[1] = 'x';
        size_t len = convertHex(buf+2, v);
        buffer_.update(len+2);
    }
    return *this;
}

//char*判断是否为空后填入buffer_
LogStream& LogStream::operator<<(const char *str)
{
    if(str)
    {
        buffer_.append(str, strlen(str));
    }
    else
    {
        buffer_.append("(null)", 6);
    }
    return *this;
}

//unsigned char*强制转换char*处理
LogStream& LogStream::operator<<(const unsigned char *str)
{
    return operator<<(reinterpret_cast<const char*>(str));
}

//string直接填入buffer_
LogStream& LogStream::operator<<(const std::string& str)
{
    buffer_.append(str.c_str(), str.size());
    return *this;
}

//kSmallBUffer(FixedBufder)对象转换为string处理
LogStream& LogStream::operator<<(const SmallBuffer& buf)
{
    *this<<buf.toString();
    return *this;
}


//GeneralTemplate对象(const char *data_)直接填入buffer_
LogStream& LogStream::operator<<(const GeneralTemplate &t)
{
    buffer_.append(t.data_, t.len_);
    return *this;
}

#if 0
// 编译命令：g++ LogStream.cc -o testlogstream -I ../base
#include <iostream>
using namespace std;
int main()
{
    // 把kSamllBuffer改为50，下面的字符串长一点，就会出现buffer存不下从而丢弃的情况
    LogStream logstream;
    logstream << -3.1415926 << &logstream << 46546465465465;
    const LogStream::SmallBuffer &buffer = logstream.buffer();
    cout << buffer.data() << endl;
    return 0;
}
#endif