#include "BaiLuConnectThread.h"

#include <utility>

Timer::~Timer() {
    stop();
    // 若析构发生在回调线程内部，stop() 不会 join，这里 join 自身会 terminate。
    // 请勿在回调中销毁 Timer 对象（正常使用不会走到这一步）。
}

bool Timer::start(std::chrono::milliseconds interval, Callback cb) {
    if (interval.count() <= 0 || !cb) {
        return false;
    }

    // 已有线程在跑就先停掉（会 join 旧线程）
    stop();

    // 说明：如果 start 是在回调线程内部调用的，旧线程就是当前线程，
    // stop() 无法 join，此时不允许重建线程。
    if (m_thread.joinable()) {
        return false;
    }

    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_interval = interval;
        m_callback = std::move(cb);
        m_stopRequested = false;
        m_intervalChanged = false;
    }

    m_running = true;
    try {
        m_thread = std::thread(&Timer::threadFunc, this);
    } catch (...) {
        m_running = false;
        return false;
    }
    return true;
}

void Timer::stop() {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!m_running && !m_thread.joinable()) {
            return;
        }
        m_stopRequested = true;
    }
    m_cv.notify_all();

    if (m_thread.joinable()) {
        // 不能在定时器线程内部 join 自己
        if (std::this_thread::get_id() != m_thread.get_id()) {
            m_thread.join();
        }
    }
    m_running = false;
}

void Timer::setInterval(std::chrono::milliseconds interval) {
    if (interval.count() <= 0) {
        return;
    }
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_interval == interval) {
            return;
        }
        m_interval = interval;
        m_intervalChanged = true;
    }
    m_cv.notify_all();
}

std::chrono::milliseconds Timer::interval() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_interval;
}

bool Timer::isRunning() const {
    return m_running.load(std::memory_order_acquire);
}

void Timer::threadFunc() {
    std::unique_lock<std::mutex> lock(m_mutex);

    auto interval = m_interval;
    auto cb = m_callback;               // callback 在 start 后不再变更，拷一份即可
    auto next = Clock::now() + interval;

    while (!m_stopRequested) {
        auto now = Clock::now();

        if (now >= next) {
            lock.unlock();
            try {
                if (cb) {
                    cb();
                }
            } catch (...) {
                // 吞掉异常，保证定时线程存活
            }
            lock.lock();

            if (m_stopRequested) {
                break;
            }

            // 从回调结束时刻重新计时，避免执行耗时导致的堆积触发
            interval = m_interval;
            next = Clock::now() + interval;
            continue;
        }

        m_cv.wait_until(lock, next);

        if (m_stopRequested) {
            break;
        }

        // setInterval 唤醒：从修改时刻重新计时
        if (m_intervalChanged) {
            m_intervalChanged = false;
            interval = m_interval;
            next = Clock::now() + interval;
        }
    }
}