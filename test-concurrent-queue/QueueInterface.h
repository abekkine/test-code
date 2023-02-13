#ifndef QUEUE_INTERFACE_H
#define QUEUE_INTERFACE_H

#include <cstdint>
#include <cstring>

#include <memory>

struct BufferUnit { 
    uint8_t * address;
    size_t size;
    BufferUnit(void * addr, const size_t sz) {
        size = sz;
        address = new uint8_t[size];
        memcpy(address, (uint8_t *)addr, size);
    }
    ~BufferUnit() {
        delete [] address;
    }
};
typedef std::shared_ptr<BufferUnit> BufferPtr;

class QueueInterface {
public:
    virtual ~QueueInterface() {}
    virtual void Push(BufferPtr buffer) = 0;
    virtual BufferPtr Pop() = 0;
    virtual size_t Size() = 0;
};

#endif // QUEUE_INTERFACE_H
