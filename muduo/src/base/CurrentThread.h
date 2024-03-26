#pragma once

#include<unistd.h>
#include<sys/syscall.h>

namespace CurrentThread
{
    extern __thread int t_cacheTid;//线程id缓冲，避免多次系统调用

    void cacheTid();//系统调用线程id

    inline int tid()//获取当前线程id
    {
        if(__builtin_expect(t_cacheTid == 0, 0))
        {
            cacheTid();
        }
        return t_cacheTid;
    }
}

