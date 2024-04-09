#pragma once

#include<unistd.h>
#include<sys/syscall.h>

//提供了一个方便的接口，用于获取当前线程的 ID，并且通过缓存避免了多次系统调用，提高了性能。
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

