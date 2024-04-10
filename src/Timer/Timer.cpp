#include"Timer.h"

void Timer::restart(TimeStamp now)
{
    if(repeat_)
    {
        expiration_= addTime(now,interval_);//设置超时时间(now+interval_)
    }
    else
    {
        expiration_ = TimeStamp::invalid();//返回0
    }
}