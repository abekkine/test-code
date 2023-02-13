#ifndef REGULAR_QUEUE_HPP
#define REGULAR_QUEUE_HPP

#include "QueueInterface.h"
#ifdef USE_SPINLOCK
#include "SpinLock.hpp"
#else
#include <mutex>
#endif

#include <vector>

class RegularQueue : public QueueInterface {
private:
    std::vector<BufferPtr> queue_;
    #ifdef USE_SPINLOCK
    SpinLock lock_;
    #else
    std::mutex mutex_;
    #endif

public:
    RegularQueue() {}
    ~RegularQueue() {}
    size_t Size() override {
        #ifdef USE_SPINLOCK
        lock_.Lock();
        #else
        std::lock_guard<std::mutex> lock(mutex_);
        #endif

        size_t size = queue_.size();

        #ifdef USE_SPINLOCK
        lock_.Unlock();
        #endif

        return size;
    }
    void Push(BufferPtr buffer) override {
        #ifdef USE_SPINLOCK
        lock_.Lock();
        #else
        std::lock_guard<std::mutex> lock(mutex_);
        #endif

        queue_.push_back(buffer);

        #ifdef USE_SPINLOCK
        lock_.Unlock();
        #endif
    }
    BufferPtr Pop() override {
        BufferPtr buffer = nullptr;
        #ifdef USE_SPINLOCK
        lock_.Lock();
        #else
        std::lock_guard<std::mutex> lock(mutex_);
        #endif
        if (queue_.size() > 0) {
            buffer = queue_.front();
            queue_.erase(queue_.begin());
        }

        #ifdef USE_SPINLOCK
        lock_.Unlock();
        #endif

        return buffer;
    }
};

#endif // REGULAR_QUEUE_HPP
