#ifndef SPINLOCK_HPP
#define SPINLOCK_HPP

#include <atomic>

class SpinLock {
private:
    std::atomic_flag locked = ATOMIC_FLAG_INIT;

public:
    void Lock() {
        while (locked.test_and_set(std::memory_order_acquire));
    }
    void Unlock() {
        locked.clear(std::memory_order_release);
    }
};

#endif // SPINLOCK_HPP
