#pragma once

#include <stdio.h>
#include <string>

//工具类，用于打开一个文件fp_，向fp_指定缓冲区buffer_(64KB)中写入数据，供LogFile调用
class FileUtil
{
public:
    explicit FileUtil(std::string &fileName);
    ~FileUtil();

    void append(const char *data, size_t len);//将数据写入文件缓冲区buffer_(64KB)
    void flush();//刷新文件缓冲区buffer_(64KB)

    // 返回已经写入了多少字节，以便LogFile根据写入数据量来判断是否需要滚动日志
    off_t wrtittenBytes() const { return wrtittenBytes_; }

private:
    size_t write(const char *data, size_t len);//将数据写入文件缓冲区buffer_(64KB)

    FILE *fp_;
    char buffer_[64*1024];//文件缓冲区大小
    off_t wrtittenBytes_;//已写入字节
};