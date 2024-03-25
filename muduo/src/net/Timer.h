#pragma once

#include "noncopyable.h"
#include "TimeStamp.h"

#include <functional>

/**
 * 定时器类：一个定时器应该需要知道超时时间，是否重复，如果是重复的定时器就需要知道执行间隔是多少，
 * 还需要知道超时后进行什么样的处理（执行回调函数）
 */

class Timer : noncopyable
{
public:
    using TimerCallback = std::function<void()>; // 超时回调函数

    Timer(TimerCallback cb, TimeStamp when, double interval)
        : callback_(std::move(cb)),
        : expiration_(when),
        : interval_(interval),
        : repeat_(interval_ > 0.0)
    {
    }

    void run() const { callback_(); }                    // 超时回调函数
    TimeStamp expiration() const { return expiration_; } // 返回初始超时时间
    bool repeat() const { return repeat_; }              // 是否为重复
    void restart(TimeStamp now);                         // 重启定时器，其实就是修改下次超时的时刻

private:
    const TimerCallback callback_; // 超时(定时器到期)回调函数
    TimeStamp expiration_;         // 初始超时时间
    const double interval_;        // 超时时间间隔，一次性定时器则该值为0
    const bool repeat_;            // 是否可重复使用
}