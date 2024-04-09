#pragma once

//删除拷贝构造函数和拷贝赋值函数，继承自本类的类都无法实现复制,
class noncopyable
{
public:
    noncopyable(const noncopyable &) = delete;
    noncopyable& operator=(const noncopyable &) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};