#pragma once

#include "TimeStamp.h"
#include "LogStream.h"

#include<stdio.h>
#include<sys/time.h>
#include<errno.h>
#include<string.h>
#include<functional>

//提取文件名
class SourceFile
{
    public:

    const char *data_;//文件名
    int size_;//文件名长度

    explicit SourceFile(Const char* filename) : data_(filename)
    {
        //找出data中最后一次出现/的位置，从而获取具体的文件名
        const char *last = strrchr(filename,'/');
        if(last)
        {
            data_ = last + 1;
        }
        size_ = static_cast<int>(strlen(data_));
    }

};

class Logger
{
    public:
        enum LogLevel
        {
            TRACE,//指出比 DEBUG 粒度更细的一些信息事件（开发过程中使用）
            DEBUG,//指出细粒度信息事件对调试应用程序是非常有帮助的（开发过程中使用）
            INFO,//表明消息在粗粒度级别上突出强调应用程序的运行过程。
            WARN,//系统能正常运行，但可能会出现潜在错误的情形。
            ERROR,//指出虽然发生错误事件，但仍然不影响系统的继续运行。
            FATAL,//指出每个严重的错误事件将会导致应用程序的退出。
            LEVEL_COUNT,
        };

        Logger(const char* file, int line);
        Logger(const char *file, int line, LogLevel level);
        Logger(const char *file, int line, LogLevel level, const char *func);
        ~Logger();

        LogStream
}