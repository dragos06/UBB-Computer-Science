#ifndef DSM_H
#define DSM_H

#include <mpi.h>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <iostream>
#include <set>
#include <atomic>

#define TAG_WRITE_REQ 1
#define TAG_PREPARE 2
#define TAG_VOTE_COMMIT 3
#define TAG_GLOBAL_COMMIT 4
#define TAG_GLOBAL_ABORT 5
#define TAG_EXIT 6
#define TAG_CAS_REQ 10
#define TAG_CAS_RESULT 11

class DSM {
private:
    int rank;
    int size;
    
    std::atomic<int> lamportClock;
    
    std::map<std::string, int> variables;
    std::map<std::string, std::set<int>> subscribers;
    
    std::function<void(std::string, int, int)> onChangeCallback;

    std::thread listenerThread;
    std::mutex dsmMutex;
    bool keepRunning;

    int getOwner(const std::string& var);
    bool isSubscriber(const std::string& var, int r);
    void updateClock(int receivedClock);

    bool runTwoPhaseCommit(const std::string& var, int newValue, int expectedValue = -1, bool isCAS = false);

    void listen();

public:
    DSM();
    ~DSM();

    void init(int argc, char** argv);
    void registerSubscription(const std::string& var, const std::set<int>& nodeRanks);
    void setCallback(std::function<void(std::string, int, int)> cb);
    
    void write(const std::string& var, int value);
    bool compareAndExchange(const std::string& var, int expected, int newValue);
    
    int getLamportClock() const { return lamportClock.load(); }
    int getRank() const { return rank; }
    void close();
};

#endif