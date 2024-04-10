#include"TimeStamp.h"

//获取当前时间戳(微秒)
TimeStamp TimeStamp::now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);//获取当前时间的秒和微秒
    int64_t seconds = tv.tv_sec;
    return TimeStamp(seconds * microSecondPerSecond + tv.tv_usec);//转换为微秒
}

//将时间戳转换为 2023/01/23/ 20:13:02.212121 或 2023/01/23 20:13:02(是否显示微秒)
std::string TimeStamp::toFormattedString(bool showMicroSecond) const
{
    char buf[64] = {0};
    time_t seconds = static_cast<time_t>(microSecondSinceEpoch_ / microSecondPerSecond);//转换为秒
    tm *tm_time = localtime(&seconds);//转换为本地时间和日期

    if(showMicroSecond)
    {
        int microSeconds = static_cast<int>(microSecondSinceEpoch_ % microSecondPerSecond);//剩余的微妙数(秒.微秒)
       snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d.%06d",
                tm_time->tm_year + 1900,
                tm_time->tm_mon + 1,
                tm_time->tm_mday,
                tm_time->tm_hour,
                tm_time->tm_min,
                tm_time->tm_sec,
                microSeconds);
    }
    else
    {
        snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d",
                tm_time->tm_year + 1900,
                tm_time->tm_mon + 1,
                tm_time->tm_mday,
                tm_time->tm_hour,
                tm_time->tm_min,
                tm_time->tm_sec);
    }
    return buf;
}


/*
 int main()
 {
     TimeStamp time;
     std::cout << time.now().toFormattedString() << std::endl;
     std::cout << time.now().toFormattedString(true) << std::endl;

     return 0; 
     }
*/
