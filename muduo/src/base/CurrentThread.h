#pragma once

#include<unistd.h>
#include<sys/syscall.h>

namespace CurrentThread
{
    extern __thread int t_cacheTid;//保存tid缓冲，避免多次系统调用

    void cacheTid();

    inline int tid()
    {
        if(__builtin_expect(t_cacheTid == 0, 0))
        {
            cacheTid();
        }
        return t_cacheTid;
    }
}

