#pragma once

#include<iostream>
#include<string.h>
#include<sys/time.h>

//用于在 C++ 程序中操作时间戳，提供了方便的接口来获取当前时间、将时间戳转换为字符串以及进行时间戳的比较等操作

class TimeStamp
{
public:
    TimeStamp() :  microSecondSinceEpoch_(0){}
    explicit TimeStamp(int64_t msSinceEpoch) : microSecondSinceEpoch_(msSinceEpoch){}

    static TimeStamp now();//获取当前时间戳(微秒)
    std::string toString() const;//转换为 "毫秒.微秒" 的形式
    std::string toFormattedString(bool showMicroSecond = false) const;//转换为日历格式
    int64_t microSecondsSinceEpoch() const {return microSecondSinceEpoch_;}//返回当前时间戳的微妙
    time_t secondsSinceEpoch() const{return microSecondSinceEpoch_ /microSecondPerSecond;}//返回当前时间戳的秒
    bool valid() const { return microSecondSinceEpoch_>0;}//判断时间戳是否有效、
    static TimeStamp invalid() {return TimeStamp();}//无效时间戳，返回0

    static const int microSecondPerSecond = 1000 * 1000;//1秒=1000 * 1000微秒
private:
    int64_t microSecondSinceEpoch_;//表示时间戳的微妙数(自Epoch以来)

};

//重载比较运算符，方便定时器比较时间戳
 inline bool operator<(TimeStamp lhs, TimeStamp rhs) 
    {
        return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
    }

inline bool operator==(TimeStamp lhs, TimeStamp rhs)
{
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

//对重复的定时任务增加时间戳
inline TimeStamp addTime(TimeStamp ts, double seconds)
{
    int64_t add = static_cast<int64_t>(seconds *TimeStamp::microSecondPerSecond);//转换为微秒
    return TimeStamp(ts.microSecondsSinceEpoch() + add);
}
