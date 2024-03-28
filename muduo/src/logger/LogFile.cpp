#include "LogFile.h"

LogFile::LogFile(const std::string &basename, off_t rollSize, bool threadSafe, int flushInterval, int checkEveryN)
    : basename_(basename),
      rollSize_(rollSize),
      flushInterval_(flushInterval),
      checkEveryN_(checkEveryN),
      count_(0),
      mutex_(threadSafe ? new std::mutex : nullptr), // 同步日志需要锁，异步日志不需要锁
      startOfPeriod_(0),
      lastRoll_(0),
      lastFlush_(0)
{
    rollFile();
}

// 滚动日志(新建文件)
//会发生混动日志的情况：
// 1）日志大小超过了设定的阈值rollSize_
// 2）写入缓冲区次数超过限制，过了0点(调用append时候)
bool LogFile::rollFile()
{
    time_t now = 0;
    std::string filename = getLogFileName(basename_, &now);
    time_t start = now / kRollPerSeconds_ * kRollPerSeconds_; // 计算经过的天数(秒数，向下取整)

    if (now > lastRoll_)
    {
        lastRoll_ = now;
        lastFlush_ = now;
        startOfPeriod_ = start;
        file_.reset(new FileUtil(filename));
        return true;
    }
    return false;
}

// 生成文件名         basename.20240311-112330.log
std::string LogFile::getLogFileName(const std::string &basename, time_t *now)
{
    std::string filename;
    filename.reserve(basename.size() + 64); // 增加容量
    filename = basename;

    char timebuf[32];
    struct tm tm;
    *now = ::time(NULL);
    localtime_r(now, &tm);

    strftime(timebuf, sizeof(timebuf), ".%Y%m%d-%H%M%S", &tm);//时间转换为指定格式字符串
    filename += timebuf;
    filename += ".log";

    return filename;
}

void LogFile::append(const char *logline, int len)
{
    if(mutex_)
    {
        std::lock_guard<std::mutex> lock(*mutex_);
        append_unlocked(logline, len);
    }
    else
    {
        append_unlocked(logline, len);
    }
}

void LogFile::append_unlocked(const char *logline, int len)
{
    file_->append(logline, len);//写入文件缓冲区

    //文件缓冲区数据超过滚动日志数据阈值
    if(file_->wrtittenBytes() > rollSize_)
    {
        // std::cout << "file_->writtenBytes()" << file_->writtenBytes() << std::endl;
        rollFile();
    }
    else
    {
        ++count_;
        //写入缓冲区次数超过次数阈值
        if(count_ >= checkEveryN_)
        {
            count_ = 0;
            time_t now = ::time(NULL);
            time_t thisPeriod = now /kRollPerSeconds_ * kRollPerSeconds_;
            
            if(thisPeriod != startOfPeriod_)//今天没有创建文件
            {
                rollFile();
            }
            else if(now-lastFlush_ > flushInterval_)//超过刷新间隔
            {
                lastFlush_ = now;
                file_->flush();
            }
        }
    }
}

void LogFile::flush()
{
    if(mutex_)
    {
        std::lock_guard<std::mutex> lock(*mutex_);//
        file_->flush();
    }
    else
    {
        file_->flush();
    }
}
