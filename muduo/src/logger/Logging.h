#pragma once

#include "TimeStamp.h"
#include "LogStream.h"

#include <stdio.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>
#include <functional>

// 提取文件名
class SourceFile
{
public:
    const char *data_; // 文件名
    int size_;         // 文件名长度

    explicit SourceFile(const char *filename) : data_(filename)
    {
        // 找出data中最后一次出现/的位置，从而获取具体的文件名
        const char *last = strrchr(filename, '/');
        if (last)
        {
            data_ = last + 1;
        }
        size_ = static_cast<int>(strlen(data_));
    }
};

// 桥接模式，具体实现交给Impl
class Logger
{
public:
    enum LogLevel
    {
        TRACE, // 指出比 DEBUG 粒度更细的一些信息事件（开发过程中使用）
        DEBUG, // 指出细粒度信息事件对调试应用程序是非常有帮助的（开发过程中使用）
        INFO,  // 表明消息在粗粒度级别上突出强调应用程序的运行过程。
        WARN,  // 系统能正常运行，但可能会出现潜在错误的情形。
        ERROR, // 指出虽然发生错误事件，但仍然不影响系统的继续运行。
        FATAL, // 指出每个严重的错误事件将会导致应用程序的退出。
        LEVEL_COUNT,
    };

    Logger(const char *file, int line);
    Logger(const char *file, int line, LogLevel level);
    Logger(const char *file, int line, LogLevel level, const char *func);
    ~Logger();

    LogStream &stream() { return impl_.stream_; } // 返回LogStream执行<<

    static LogLevel logLevel();              // 返回日志级别
    static void setLogLevel(LogLevel level); // 设置日志级别

    using outputFunc = std::function<void(const char *msg, int len)>; // 输出
    using flushFunc = std::function<void()>;                          // 刷新缓冲区

    static void setOutput(outputFunc); // 设置日志输出位置
    static void setFlush(flushFunc);

private:
    // 负责Logger主要实现，提供组装一条完整log消息的功能。
    // 日期      时间     微秒     线程  级别  正文     源文件名:       行号
    // 20220306 09:15:44.681220Z  4013 WARN  Hello - Logging_test.cpp:75
    class Impl
    {
    public:
        using LogLevel = Logger::LogLevel;

        Impl(LogLevel level, int savedErrno, const char *file, int line);

        void formatTime(); // 将时间转换为字符串形式输出
        void finish();     // 添加一条log消息的后缀,比如文件名、行号、换行符

        TimeStamp time_;      // 获取当前时间
        LogStream stream_;    // 用于格式化用户log数据, 提供operator<<接口, 保存log消息
        LogLevel level_;      // 日志等级
        int line_;            // 源代码所在行
        SourceFile basename_; // 源代码所在文件名(不含路径)信息
    };

    Impl impl_;
};

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel logLevel() { return g_logLevel; }

const char *getErrnoMsg(int savedErrno); // 获取errno信息

// 定义了一系列LOG_开头的宏，便于用户以C++风格记录日志
#define LOG_TRACE                    \
    if (logLevel() <= Logger::TRACE) \
    Logger(__FILE__, __LINE__, Logger::TRACE, __func__).stream()
#define LOG_DEBUG                    \
    if (logLevel() <= Logger::DEBUG) \
    Logger(__FILE__, __LINE__, Logger::DEBUG, __func__).stream()
#define LOG_INFO                    \
    if (logLevel() <= Logger::INFO) \
    Logger(__FILE__, __LINE__).stream()
#define LOG_WARN Logger(__FILE__, __LINE__, Logger::WARN).stream()
#define LOG_ERROR Logger(__FILE__, __LINE__, Logger::ERROR).stream()
#define LOG_FATAL Logger(__FILE__, __LINE__, Logger::FATAL).stream()
