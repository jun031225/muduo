#pragma once

#include"noncopyable.h"

#include<assert.h>
#include<string.h>
#include<strings.h>
#include<string>


//自定义的Buffer工具类，可以申请制定大小的空间的内存区域，并实现了一些接口方便
//从buffer中写入数据或者取出数据。异步日志就需要前端先将日志信息写入Buffer，
//然后后端从buffer中取出数据写入stdout或者文件，

//Buffer默认大小
const int kSmallBuffer = 4096;//前端
const int kLargeBUffer = 4086*1024;//后端

template<int SIZE>
class FixedBuffer : noncopyable
{
    private:
    const char *end() const{return data_ + sizeof(data_);}//指向文件尾
    char data_[SIZE];
    char *cur_;//记录当前data_中已经写到了什么位置

    public:
        FixedBuffer() : cur_(data_){}

        //向FixedBuffer中添加数据，空间不够则不做处理
        void append(const char *buf, size_t len)
        {
            if(static_cast<size_t>(avail()) > len)
            {
                ::memcpy(cur_, buf, len);
                cur_ +=len;
            }
        }

        const char* data() const{return data_;}//返回FixedBuffer首地址
        int length() const {return static_cast<int>(cur_ - data_);}//返回写入数据长度
        char* current() const{return cur_;}//返回当前位置
        int avail() const{return static_cast<int>(end() - cur_);}//返回剩余空间长度

        void update(size_t len){cur_ += len;}//更新当前位置

        void reset(){cur_ = data_;}
        void bzero(){::bzero(data_, sizeof(data_));}//清空

        std::string toString() const{return std::string(data_, length());}//将写入数据转换为字符串

    /*------------------------------------*/
    /*|xxxxxxxxxxxxx|<---   avail() ---->|*/
    /*------------------------------------*/
    /*data_        cur_              end()*/
};



