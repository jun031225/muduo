#pragma once

#include "FileUtil.h"

#include <mutex>
#include <memory>

//为数据写入文件提供缓冲区(64KB)，供AsyncLogging调用

class LogFile
{
public:
    LogFile(const std::string &basename, off_t rollSize, bool threadSafe = true, int flushInterval = 3, int checkEveryN = 1024);
    ~LogFile() = default;

    void append(const char *logline, int len);
    void flush();    // 刷新文件缓冲区buffer_(64KB)
    bool rollFile(); // 滚动日志，相当于创建一个新的文件，用来存储日志
private:
    //根据当前时间生成一个文件名并返回   basename.20240311-112330.log
    static std::string getLogFileName(const std::string &basename, time_t *now);
    void append_unlocked(const char *logline, int len);

    const std::string basename_;
    const off_t rollSize_; // 是否滚动日志的阈值，file_的缓冲区buffer_(64KB)中的数据超过该值就会滚动日志
    const int flushInterval_;//刷新时间间隔
    const int checkEveryN_;//写入文件缓冲区次数的阈值，超过则写入文件

    int count_;//记录写入文件缓冲区次数，超过checkEveryN则刷新一次

    std::unique_ptr<std::mutex> mutex_;
    time_t startOfPeriod_;//记录最后一个日志文件创建时间(天)
    time_t lastRoll_;//最后一次滚动日志的时间
    time_t lastFlush_;//最后一次刷新的时间
    std::unique_ptr<FileUtil> file_;

    //用于日志文件的滚动，确保日志文件按照天进行切分，每天一个日志文件，方便管理和归档。
     //(60*60*24)一天
};const static int kRollPerSeconds_ = 86400;