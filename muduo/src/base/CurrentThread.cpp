#include"CurrentThread.h"

namespace CurrentThread
{
    __thread int t_cacheTid =0;

    void cacheTid()
    {
        if(t_cacheTid == 0)
        {
            t_cacheTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }
} 
