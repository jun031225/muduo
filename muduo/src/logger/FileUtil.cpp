#include "FileUtil.h"
#include "Logging.h"

FileUtil::FileUtil(std::string &fileName) : 
//追加模式打开一个文件，并以二进制形式进行读写,
//即文件指针会被设置到文件的末尾，这样写入操作会从文件的末尾开始。
//如果文件不存在，则会尝试创建文件
fp_(::fopen(fileName.c_str(), "ae")),
                                            wrtittenBytes_(0)
{
    ::setbuffer(fp_, buffer_, sizeof(buffer_)); // 将文件缓冲区设为自定义buffer_
}

FileUtil::~FileUtil()
{
    ::fclose(fp_);
}

// 写入文件(缓冲区)
void FileUtil::append(const char *data, size_t len)
{
    size_t written = 0;    // 记录已经写入的数据大小
    while (written != len) // 循环写入
    {
        size_t remain = len - written; // 未写入的数据大小
        size_t n = FileUtil::write(data + written, remain);
        if (n != remain) // 写入出现错误
        {
            int err = ferror(fp_);
            if (err)
            {
                fprintf(stderr, "FileUtil::appen() failed %s\n", getErrnoMsg(err));
            }
        }
        written += n;//更新写入数据大小
    }
    wrtittenBytes_ += written;//更新已写入数据
}

//刷新缓冲区
void FileUtil::flush()
{
    ::fflush(fp_);
}

// 写入文件(缓冲区)
size_t FileUtil::write(const char *data, size_t len)
{
    // fwrite_unlocked() 是一个线程不安全的版本，它不会自动获取文件锁，因此可能更快，但也更危险。
    // 必须自行确保线程同步，以避免竞争条件和数据损坏
    return ::fwrite_unlocked(data, 1, len, fp_);
}