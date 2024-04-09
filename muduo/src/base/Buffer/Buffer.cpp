#include"Buffer.h"

#include<errno.h>
#include<sys/uio.h>
#include<unistd.h>

const char Buffer::kCRLF[] = "\r\n";

ssize_t Buffer::readFd(int fd, int *saveErrno)
{
    //额外栈空间，buffer空间不足时暂存数据，待分配足够空间后，再将数据交给buffer
    char extraBuf[65536] = {0};//(64KB)

    struct iovec vec[2];
    const size_t writable = writableBytes();

    //可写空间与额外栈空间,当可写空间被写满后则写入额外栈空间
    vec[0].iov_base = begin() + writerIndex_;
    vec[0].iov_len = writable;
    vec[1].iov_base = extraBuf;
    vec[1].iov_len = sizeof(extraBuf);

    const int iovcnt = (writable < sizeof(extraBuf)) ? 2 : 1;
    const ssize_t n = ::readv(fd, vec, iovcnt);

    if(n < 0)
    {
        *saveErrno = errno;
    }
    else if(n <= writable)//可读空间足够
    {
        writerIndex_ += n;
    }
    else//可读空间不足，对buffer扩容后，将extrabuf中数据写入buffer
    {
        writerIndex_ = buffer_.size();
        append(extraBuf, n-writable);
    }
    return n;
}


//向fd写入数据(tcp发送缓冲区满)
ssize_t Buffer::writeFd(int fd, int *saveErrno)
{
    ssize_t n = ::write(fd, peek(), readableBytes());
    if(n < 0)
    {
        *saveErrno = errno;
    }
    return n;
}