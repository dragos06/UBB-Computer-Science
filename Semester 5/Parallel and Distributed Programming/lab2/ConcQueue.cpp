#include "ConcQueue.h"

using namespace std;

ConcQueue::ConcQueue(int capacity)
{
    this->size = 0;
    this->capacity = capacity;
    this->queue = new int[this->capacity];
}

ConcQueue::~ConcQueue() {
    delete[] this->queue;
}

void ConcQueue::enqueue(int number)
{
    unique_lock<std::mutex> lock(this->mutex);
    this->not_full.wait(lock, [this]() { return this->size < this->capacity; });

    this->queue[size++] = number;

    this->not_empty.notify_one();
}

void ConcQueue::dequeue()
{
    unique_lock<std::mutex> lock(this->mutex);
    not_empty.wait(lock, [this]() { return size > 0; });

    for(int i = 0; i < this->size - 1; i++) {
        this->queue[i] = this->queue[i + 1];
    }

    this->size--;

    this->not_full.notify_one();
}

int ConcQueue::top()
{
    unique_lock<std::mutex> lock(this->mutex);
    not_empty.wait(lock, [this]() { return size > 0; });
    
    return this->queue[0];   
}
