#ifndef CONCURRENT_QUEUE_HPP
#define CONCURRENT_QUEUE_HPP

#include "QueueInterface.h"

#include <atomic>

class ConcurrentQueue : public QueueInterface {
private:
    size_t size_;
    struct Node {
        Node * prev;
        Node * next;
        BufferPtr buffer;
    };
    Node * head_;
    Node * tail_;

public:
    ConcurrentQueue() {
        size_ = 0;
        head_ = nullptr;
        tail_ = nullptr;
    }
    ~ConcurrentQueue() {}
    size_t Size() override {
        return size_;
    }

    void Push(BufferPtr buffer) override {
        Node * n = new Node;
        n->buffer = buffer;
        if (head_ == nullptr) {
            n->prev = nullptr;
            n->next = nullptr;
            head_ = n;
            tail_ = n;
        } else {
            n->prev = tail_;
            n->next = nullptr;
            tail_->next = n;
            tail_ = n;
        }
        ++size_;
    }

    BufferPtr Pop() override {
        BufferPtr bu;
        if (size_ == 0) {
            // Nothing to pop
            bu = nullptr;
        }
        else if (size_ == 1) {
            // Head and Tail is same.
            bu = head_->buffer;
            delete head_;
            head_ = tail_ = nullptr;
            size_ = 0;
        } else {
            // Head & Tail is different.
            Node * tailTemp = tail_;
            bu = tail_->buffer;
            tail_ = tail_->prev;
            tail_->next = nullptr;
            delete tailTemp;
            --size_;
        }
        return bu;
    }
};

#endif // CONCURRENT_QUEUE_HPP
