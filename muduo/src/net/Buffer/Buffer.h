#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

/// +-------------------+------------------+------------------+
/// | prependable bytes  |  readable bytes  |  writable bytes  |
/// |kCheapPrepend|被读出|     (CONTENT)    |                  |
/// +-------------------+------------------+------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size

// 注意，readable bytes空间才是要服务端要发送的数据，writable bytes空间是从socket读来的数据存放的地方。
// 具体的说：是write还是read都是站在buffer角度看问题的，不是站在和客户端通信的socket角度。当客户socket有数据发送过来时，
// socket处于可读，所以我们要把socket上的可读数据写如到buffer中缓存起来，所以对于buffer来说，当socket可读时，是需要向buffer中
// write数据的，因此 writable bytes 指的是用于存放socket上可读数据的空间, readable bytes同理
// writable bytes(可写空间)用于存放写入缓冲数据的空间，数据写入则writeIndex_增加，可写空间减小，可读空间增加
// readabel bytes(可读空间)用于存放读出缓冲数据的空间，数据读出则readIndex_增加，可读空间减小，
class Buffer
{
public:
    static const size_t kCheapPrepend = 8;  // 前8个字节用于记录数据长度，用于解决粘包
    static const size_t kInitalSize = 1024; // 初始可读/可写大小(1KB)

    explicit Buffer(size_t initalSize = kInitalSize)
        : buffer_(kCheapPrepend + initalSize),
          readerIndex_(kCheapPrepend),
          writerIndex_(kCheapPrepend)
    {
    }
    
    //从fd读取数据(可写空间-)
    ssize_t readFd(int fd, int *saveErrno);
    //写入数据到fd(可读空间-)
    ssize_t writeFd(int fd, int *saveErrno);

     // 从可读空间取出可读数据(string)
    std::string retrieveAllAsString() { return retrieveAsString(readableBytes()); }
    std::string retrieveAsString(size_t len)
    {
        std::string result(peek(), len);
        reposition(len);
        return result;
    }

    //写入数据到可写空间
    void append(const std::string &str)
    {
        append(str.data(), str.size());
    }

    void append(const char *data, size_t len)
    {
        ensureWritableBytes(len);
        std::copy(data, data + len, beginWrite());
        writerIndex_ += len;
    }

    // 查找buffer_中是否有"\r\n"
    const char *findCRLF() const
    {
        const char *crlf = std::search(peek(), beginWrite(), kCRLF, kCRLF + 2);
        return crlf == beginWrite() ? NULL : crlf;
    }

    //复位空间(取出数据到end位置)
    void repositionUntil(const char *end)
    {
        assert(peek() <= end);
        assert(end <= beginWrite());
        reposition(end - peek());
    }

    //复位空间(取出len长度数据)
    void reposition(size_t len)
    {
        if (len < readableBytes()) // 取出部分数据
        {
            readerIndex_ += len;
        }
        else // 取出全部数据
        {
            readerIndex_ = kCheapPrepend;
            writerIndex_ = kCheapPrepend;
        }
    }

    // 复位到初始位置
    void repositionAll()
    {
        readerIndex_ = kCheapPrepend;
        writerIndex_ = kCheapPrepend;
    }

    // 确保可写空间充足
    void ensureWritableBytes(size_t len)
    {
        if (writableBytes() < len)
        {
            makeSpace(len);
        }
    }

    // 可读空间大小
    size_t readableBytes() const
    {
        return writerIndex_ - readerIndex_;
    }

    // 可写空间大小
    size_t writableBytes() const
    {
        return buffer_.size() - writerIndex_;
    }

    // 预留空间大小(kCheapPrepend+已被读出的空闲区域)
    size_t prependableBytes() const
    {
        return readerIndex_;
    }

    // 返回可读空间起始地址
    const char *peek() const
    {
        return begin() + readerIndex_;
    }

    // 返回可写空间起始地址
    char *beginWrite()
    {
        return begin() + writerIndex_;
    }

    const char *beginWrite() const
    {
        return begin() + writerIndex_;
    }

private:
    // 获取起始地址
    char *begin()
    {
        return &(*buffer_.begin());
    }
    const char *begin() const
    {
        return &(*buffer_.begin());
    }

    // 扩容
    void makeSpace(int len)
    {
        // 当可写空间+已被读出的空闲区域 < 要写入数据的长度 扩容
        if (writableBytes() + prependableBytes() - kCheapPrepend < len)
        {
            buffer_.resize(writerIndex_ + len);
        }
        else // 调整可读空间与可写空间
        {
            size_t readable = readableBytes();
            // 空间前移覆盖已被读出的空闲区域
            std::copy(begin() + readerIndex_, begin() + writerIndex_, begin() + kCheapPrepend);
            // 更新游标
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readable;
        }
    }

    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
    static const char kCRLF[]; // 存储"\r\n"
};