#include "RegularQueue.hpp"
#include "ConcurrentQueue.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#ifdef USE_SLEEP
#include <chrono>
#endif
#include <atomic>

int main() {

    // std::shared_ptr<QueueInterface> queue = std::make_shared<RegularQueue>();
    std::shared_ptr<QueueInterface> queue = std::make_shared<ConcurrentQueue>();

    std::vector<std::string> word_list = {
        "This", "is", "a", "list", "of", "strings", "to", "test", "concurrent", "queue", "implementation"
    };

    std::atomic<bool> quit(false);
    std::thread thread_([&](){
        BufferPtr bu = nullptr;
        while (! quit) {
            bu = queue->Pop();
            if (bu != nullptr) {
                std::string s((char *)(bu->address));
                std::cout << "S[" << s << "]\n";
            }
            #ifdef USE_SLEEP
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            #endif
        }
    });

    #ifdef REPEAT_NUMBER
    for (int i=0; i<REPEAT_NUMBER; ++i)
    #endif
    for (auto & w : word_list) {
        auto bu = std::make_shared<BufferUnit>((void *)w.data(), w.size());
        queue->Push(bu);
    }

    while (queue->Size() != 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    quit = true;
    thread_.join();

    return 0;
}

