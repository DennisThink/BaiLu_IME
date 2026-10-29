#pragma once
/*
* 在输入法中开启一个新的线程，进行比较耗时的操作
* 
* 
*/
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

class Timer {
public:
    using Clock = std::chrono::steady_clock;
    using Callback = std::function<void()>;

    Timer() = default;
    ~Timer();

    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;

    // 启动定时器。若已在运行，会先停止再以新参数启动。
    // interval 必须 > 0，cb 不能为空，否则返回 false。
    bool start(std::chrono::milliseconds interval, Callback cb);

    // 请求停止。若在非定时器线程中调用，会阻塞等待线程退出；
    // 若在回调内部调用，只置停止标志，不 join。
    void stop();

    // 运行中修改间隔，从调用时刻起重新计时。未运行时只更新参数。
    void setInterval(std::chrono::milliseconds interval);

    std::chrono::milliseconds interval() const;
    bool isRunning() const;

private:
    void threadFunc();

    std::thread m_thread;
    mutable std::mutex m_mutex;
    std::condition_variable m_cv;
    std::chrono::milliseconds m_interval{1000};
    Callback m_callback;
    bool m_stopRequested = false;
    bool m_intervalChanged = false;
    std::atomic<bool> m_running{false};
};