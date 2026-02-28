#include "DSM.h"
#include <cstring>

DSM::DSM() : rank(0), size(0), lamportClock(0), keepRunning(true) {}

DSM::~DSM() { close(); }

void DSM::init(int argc, char** argv) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (provided < MPI_THREAD_MULTIPLE) {
        if(rank == 0) std::cerr << "Error: MPI_THREAD_MULTIPLE not supported." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    listenerThread = std::thread(&DSM::listen, this);
}

int DSM::getOwner(const std::string& var) {
    if (subscribers.find(var) != subscribers.end() && !subscribers[var].empty()) {
        return *subscribers[var].begin();
    }
    return 0;
}

bool DSM::isSubscriber(const std::string& var, int r) {
    if (subscribers.find(var) == subscribers.end()) return false;
    return subscribers[var].count(r) > 0;
}

void DSM::updateClock(int receivedClock) {
    int current = lamportClock.load();
    while (receivedClock > current) {
        if (lamportClock.compare_exchange_weak(current, receivedClock + 1)) {
            break;
        }
        current = lamportClock.load();
    }
    lamportClock++; 
}

void DSM::registerSubscription(const std::string& var, const std::set<int>& nodeRanks) {
    std::lock_guard<std::mutex> lock(dsmMutex);
    subscribers[var] = nodeRanks;
    variables[var] = 0;
}

void DSM::setCallback(std::function<void(std::string, int, int)> cb) {
    std::lock_guard<std::mutex> lock(dsmMutex);
    onChangeCallback = cb;
}

bool DSM::runTwoPhaseCommit(const std::string& var, int newValue, int expectedValue, bool isCAS) {
    if (isCAS && variables[var] != expectedValue) {
        return false; 
    }

    lamportClock++;
    int currentClock = lamportClock.load();
    int nameLen = var.size();

    std::vector<int> participants;
    for (int p : subscribers[var]) {
        if (p != rank) participants.push_back(p);
    }

    for (int p : participants) {
        MPI_Send(&nameLen, 1, MPI_INT, p, TAG_PREPARE, MPI_COMM_WORLD);
        MPI_Send(var.c_str(), nameLen, MPI_CHAR, p, TAG_PREPARE, MPI_COMM_WORLD);
        MPI_Send(&newValue, 1, MPI_INT, p, TAG_PREPARE, MPI_COMM_WORLD);
        MPI_Send(&currentClock, 1, MPI_INT, p, TAG_PREPARE, MPI_COMM_WORLD);
    }

    for (int p : participants) {
        int vote;
        MPI_Recv(&vote, 1, MPI_INT, p, TAG_VOTE_COMMIT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int oldVal = variables[var];
    variables[var] = newValue;
    if (onChangeCallback) onChangeCallback(var, oldVal, newValue);

    lamportClock++;
    currentClock = lamportClock.load();
    for (int p : participants) {
        MPI_Send(&nameLen, 1, MPI_INT, p, TAG_GLOBAL_COMMIT, MPI_COMM_WORLD);
        MPI_Send(var.c_str(), nameLen, MPI_CHAR, p, TAG_GLOBAL_COMMIT, MPI_COMM_WORLD);
        MPI_Send(&newValue, 1, MPI_INT, p, TAG_GLOBAL_COMMIT, MPI_COMM_WORLD);
        MPI_Send(&currentClock, 1, MPI_INT, p, TAG_GLOBAL_COMMIT, MPI_COMM_WORLD);
    }
    
    return true;
}

void DSM::write(const std::string& var, int value) {
    if (!isSubscriber(var, rank)) {
        std::cerr << "[P" << rank << "] Write denied (not subscriber)" << std::endl;
        return;
    }

    int owner = getOwner(var);
    if (owner == rank) {
        std::lock_guard<std::mutex> lock(dsmMutex);
        runTwoPhaseCommit(var, value);
    } else {
        std::lock_guard<std::mutex> lock(dsmMutex);
        lamportClock++;
        int currentClock = lamportClock.load();
        
        int nameLen = var.size();
        MPI_Send(&nameLen, 1, MPI_INT, owner, TAG_WRITE_REQ, MPI_COMM_WORLD);
        MPI_Send(var.c_str(), nameLen, MPI_CHAR, owner, TAG_WRITE_REQ, MPI_COMM_WORLD);
        MPI_Send(&value, 1, MPI_INT, owner, TAG_WRITE_REQ, MPI_COMM_WORLD);
        MPI_Send(&currentClock, 1, MPI_INT, owner, TAG_WRITE_REQ, MPI_COMM_WORLD);
    }
}

bool DSM::compareAndExchange(const std::string& var, int expected, int newValue) {
    if (!isSubscriber(var, rank)) return false;

    int owner = getOwner(var);
    
    if (owner == rank) {
        std::lock_guard<std::mutex> lock(dsmMutex);
        return runTwoPhaseCommit(var, newValue, expected, true);
    } else {
        int currentClock;
        {
            std::lock_guard<std::mutex> lock(dsmMutex);
            lamportClock++; 
            currentClock = lamportClock.load();
        
            int nameLen = var.size();
            MPI_Send(&nameLen, 1, MPI_INT, owner, TAG_CAS_REQ, MPI_COMM_WORLD);
            MPI_Send(var.c_str(), nameLen, MPI_CHAR, owner, TAG_CAS_REQ, MPI_COMM_WORLD);
            int params[2] = {expected, newValue};
            MPI_Send(params, 2, MPI_INT, owner, TAG_CAS_REQ, MPI_COMM_WORLD);
            MPI_Send(&currentClock, 1, MPI_INT, owner, TAG_CAS_REQ, MPI_COMM_WORLD);
        } 
        int result;
        
        MPI_Recv(&result, 1, MPI_INT, owner, TAG_CAS_RESULT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        return (result == 1);
    }
}

void DSM::listen() {
    while (keepRunning) {
        MPI_Status status;
        int flag;
        MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &status);
        
        if (!flag) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            continue;
        }

        int source = status.MPI_SOURCE;
        int tag = status.MPI_TAG;

        if (tag == TAG_EXIT) {
            int dummy;
            MPI_Recv(&dummy, 1, MPI_INT, source, TAG_EXIT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            break;
        }
        else if (tag == TAG_PREPARE) {
            int nameLen;
            MPI_Recv(&nameLen, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            char* buf = new char[nameLen + 1];
            MPI_Recv(buf, nameLen, MPI_CHAR, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            buf[nameLen] = '\0';
            std::string varName(buf);
            delete[] buf;
            
            int val, senderClock;
            MPI_Recv(&val, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&senderClock, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            std::lock_guard<std::mutex> lock(dsmMutex);
            updateClock(senderClock);

            int vote = 1;
            MPI_Send(&vote, 1, MPI_INT, source, TAG_VOTE_COMMIT, MPI_COMM_WORLD);
        }
        else if (tag == TAG_GLOBAL_COMMIT) {
            int nameLen;
            MPI_Recv(&nameLen, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            char* buf = new char[nameLen + 1];
            MPI_Recv(buf, nameLen, MPI_CHAR, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            buf[nameLen] = '\0';
            std::string varName(buf);
            delete[] buf;
            
            int val, senderClock;
            MPI_Recv(&val, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&senderClock, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            std::lock_guard<std::mutex> lock(dsmMutex);
            updateClock(senderClock);
            
            int old = variables[varName];
            variables[varName] = val;
            if (onChangeCallback) onChangeCallback(varName, old, val);
        }
        else if (tag == TAG_WRITE_REQ) {
            int nameLen;
            MPI_Recv(&nameLen, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            char* buf = new char[nameLen + 1];
            MPI_Recv(buf, nameLen, MPI_CHAR, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            buf[nameLen] = '\0';
            std::string varName(buf);
            delete[] buf;

            int val, senderClock;
            MPI_Recv(&val, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&senderClock, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            std::lock_guard<std::mutex> lock(dsmMutex);
            updateClock(senderClock);
            
            if (isSubscriber(varName, source)) {
                runTwoPhaseCommit(varName, val);
            }
        }
        else if (tag == TAG_CAS_REQ) {
            int nameLen;
            MPI_Recv(&nameLen, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            char* buf = new char[nameLen + 1];
            MPI_Recv(buf, nameLen, MPI_CHAR, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            buf[nameLen] = '\0';
            std::string varName(buf);
            delete[] buf;

            int params[2];
            MPI_Recv(params, 2, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            int senderClock;
            MPI_Recv(&senderClock, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            int result = 0;
            {
                std::lock_guard<std::mutex> lock(dsmMutex);
                updateClock(senderClock);

                if (isSubscriber(varName, source)) {
                    bool success = runTwoPhaseCommit(varName, params[1], params[0], true);
                    result = success ? 1 : 0;
                }
            }
            MPI_Send(&result, 1, MPI_INT, source, TAG_CAS_RESULT, MPI_COMM_WORLD);
        }
    }
}

void DSM::close() {
    if (keepRunning) {
        keepRunning = false;
        int dummy = 0;
        MPI_Send(&dummy, 1, MPI_INT, rank, TAG_EXIT, MPI_COMM_WORLD);
        if (listenerThread.joinable()) listenerThread.join();
        MPI_Finalize();
    }
}