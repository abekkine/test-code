#ifndef CONCURRENT_QUEUE_HPP
#define CONCURRENT_QUEUE_HPP

#include "QueueInterface.h"
#include "SpinLock.hpp"

#include <atomic>

class ConcurrentQueue : public QueueInterface {
private:
    std::atomic<size_t> size_;
    struct Node {
        BufferPtr buffer;
        Node * prev;
        std::mutex m;

        explicit Node(BufferPtr bu) : Node(bu, nullptr) {}
        explicit Node(BufferPtr bu, Node* p) : buffer(bu), prev(p) {}
    };
    Node* head_;
    Node* tail_;

public:
    ConcurrentQueue() {
        size_ = 0;
        head_ = new Node(nullptr);
    }
    ~ConcurrentQueue() {}
    size_t Size() override {
        return size_;
    }

    void Push(BufferPtr buffer) override {
        Node* new_node = new Node(buffer);
        
        ++size_;
    }

    BufferPtr Pop() override {
        BufferPtr bu;
        return bu;
    }
};

#endif // CONCURRENT_QUEUE_HPP
