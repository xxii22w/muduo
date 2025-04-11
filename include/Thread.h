#pragma once

#include <iostream>
#include <thread>
#include <memory>
#include <unistd.h>
#include <functional>
#include <string>
#include <atomic>

#include "noncopyable.h"

class Thread : noncopyable
{
public:
    using ThreadFunc = std::function<void()>;

    explicit Thread(ThreadFunc func, const std::string& name = std::string());
    ~Thread();

    void start();
    void join();

    bool started() {return started_;}
    pid_t tid() {return tid_;}
    const std::string& name() {return name_;}

    static int numCreated() {return numCreated_;}

private:
    void setDefaultName();

    bool started_;
    bool joined_;
    std::shared_ptr<std::thread> thread_;
    pid_t tid_; // 在线程创建时再绑定
    ThreadFunc func_; // 线程回调函数
    std::string name_; 
    static std::atomic_int numCreated_; // 线程创建的数量
};

