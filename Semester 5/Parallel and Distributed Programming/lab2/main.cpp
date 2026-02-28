#include "ConcQueue.h"
#include <thread>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

int N = 1000;
int QUEUE_SIZE = 1000;

vector<int> vector1(N);
vector<int> vector2(N);
int globalSum = 0;
ConcQueue* queue = new ConcQueue{QUEUE_SIZE};

void generateVectors() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 100);

    for(int i = 0; i < N; i++) {
        vector1[i] = dist(gen);
        vector2[i] = dist(gen);
    }
}

int verify() {
    int result = 0;
    for(int i = 0; i < N; i++) {
        result += vector1[i] * vector2[i];
    }
    return result;
}

void prod() {
    for(int i = 0; i < N; i++) {
        int prod = vector1[i] * vector2[i];
        queue->enqueue(prod);
    }
}

void sum() {
    for(int i = 0; i < N; i++) {
        int elem = queue->top();
        queue->dequeue();
        globalSum += elem;
    }
}

int main() {
    generateVectors();

    auto start = chrono::high_resolution_clock::now();

    thread producer(prod);
    thread consumer(sum);

    producer.join();
    consumer.join();
    
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    int expected = verify();
    cout<<"Sequential result: " << expected << endl;
    cout<<"Concurrent result: " << globalSum << endl;
    cout << "Execution time: " << elapsed.count() << " s" << endl;
    
    if (expected != globalSum)
        cerr << "ERROR: Mismatch detected!" << endl;
    else
        cout << "Correct result." << endl;

    return 0;
}