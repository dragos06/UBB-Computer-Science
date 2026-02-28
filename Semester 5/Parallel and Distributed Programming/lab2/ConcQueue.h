#pragma once
#include <mutex>
#include <condition_variable>

class ConcQueue {
private:
    int* queue;
    int capacity;
    int size;
    
    std::mutex mutex;
    std::condition_variable not_full;
    std::condition_variable not_empty;
public:
    ConcQueue(int capacity);
    ~ConcQueue();
    void enqueue(int number);
    void dequeue();
    int top();
};
