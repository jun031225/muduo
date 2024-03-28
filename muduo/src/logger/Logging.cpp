#include "Logging.h"
#include "CurrentThread.h"

// 封装三个线程局部存储（TLS）变量
// 每个线程都有自己的 t_errnobuf，因此不会出现多个线程同时尝试写入或读取同一缓冲区的情况
namespace ThreadInfo
{
    __thread char t_errnobuf[512]; // 存储错误消息的缓存区
    __thread char t_time[64];      // 储存时间信息的缓存区
    __thread time_t t_lastSecond;  // 存储上次记录时间(秒)
};


Logger::Impl::Impl(Logger::LogLevel level, int savedErrno, const char *file, int line)
    : time_(TimeStamp::now()),
      stream_(),
      level_(level),
      line_(line),
      basename_(file)
{
    formatTime();                                       // 将时间写入流
    //CurrentThread::tid();
    //stream_ << GeneralTemplate(CurrentThread::tidString(), static_cast<unsigned int>(CurrentThread::tidStringLength()));
    stream_ << GeneralTemplate(getLevelName[level], 6); // 将日志等级写入流

    // 将错误信息写入流
    if (savedErrno != 0)
    {
        stream_ << getErrnoMsg(savedErrno) << "(errno = " << savedErrno << ")";
    }
}

Logger::Logger(const char *file, int line) : impl_(INFO, 0, file, line) {}
Logger::Logger(const char *file, int line, Logger::LogLevel level) : impl_(level, 0, file, line) {}
Logger::Logger(const char *file, int line, Logger::LogLevel level, const char *func) : impl_(level, 0, file, line)
{
    impl_.stream_ << func << ' ';
}

Logger::~Logger()
{
    impl_.finish();

    // 获取buffer_
    const LogStream::SmallBuffer &buf(stream().buffer());

    // 写入标准输出
    g_output(buf.data(), buf.length());

    // FATAL等级终止程序
    if (impl_.level_ == FATAL)
    {
        g_flush();
        abort();
    }
}

// Timestamp::toFmattedString方法的思路，只不过这里需要输出到流
void Logger::Impl::formatTime()
{
    // 当前时间转换为秒.微秒的形式
    TimeStamp time = TimeStamp::now();
    time_t seconds = static_cast<time_t>(time.microSecondsSinceEpoch() / TimeStamp::microSecondPerSecond);
    int microSeconds = static_cast<int>(time.microSecondsSinceEpoch() % TimeStamp::microSecondPerSecond);

    struct tm *tm_time = localtime(&seconds);

    // 将时间（秒）写入时间buffer
    snprintf(ThreadInfo::t_time, sizeof(ThreadInfo::t_time), "%4d/%02d/%02d %02d:%02d:%02d",
             tm_time->tm_year + 1900,
             tm_time->tm_mon + 1,
             tm_time->tm_mday,
             tm_time->tm_hour,
             tm_time->tm_min,
             tm_time->tm_sec);

    // 记录上次时间
    ThreadInfo::t_lastSecond = seconds;

    // 写入微妙
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "%06d", microSeconds);

    // 写入时间到输出流
    stream_ << GeneralTemplate(ThreadInfo::t_time, 17) << GeneralTemplate(buf, 7);
}

// Log结尾(文件名，行号)
void Logger::Impl::finish()
{
    stream_ << " - " << GeneralTemplate(basename_.data_, basename_.size_) << ':' << line_ << '\n';
}

const char *getErrnoMsg(int savedErrno)
{
    // 线程安全地获取指向错误消息的指针
    return strerror_r(savedErrno, ThreadInfo::t_errnobuf, sizeof(ThreadInfo::t_errnobuf));
}

// 根据Level返回Level名字
const char *getLevelName[Logger::LogLevel::LEVEL_COUNT]{
    "TRACE", // 0
    "DEBUG", // 1
    "INFO",  // 2
    "WARN",  // 3
    "ERROR", // 4
    "FATAL", // 5
};

// 初始日志等级为INFO
Logger::LogLevel initLogLevel()
{
    return Logger::INFO;
}

Logger::LogLevel g_logLevel = initLogLevel();

// 默认写入标准输出
static void defaultOutput(const char *data, int len)
{
    fwrite(data, 1, static_cast<size_t>(len), stdout);
}

// 默认刷新标准输出缓冲区
static void defaultFlush()
{
    fflush(stdout);
}

// 设置默认写入和刷新函数
Logger::outputFunc g_output = defaultOutput;
Logger::flushFunc g_flush = defaultFlush;

//下面函数修改默认日志等级，输出位置，刷新
void Logger::setLogLevel(Logger::LogLevel level)
{
    g_logLevel = level;
}

void Logger::setOutput(outputFunc out)
{
    g_output = out;
}

void Logger::setFlush(flushFunc flush)
{
    g_flush = flush;
}


int main()
{
    std::cout<<"test";
    return 0;
}


