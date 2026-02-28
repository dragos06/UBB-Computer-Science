#include "DSM.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<int> local_A(0);
std::atomic<int> local_B(0);

int main(int argc, char** argv) {
    DSM dsm;
    dsm.init(argc, argv);

    int rank = dsm.getRank();
    
    dsm.registerSubscription("A", {0, 1, 2});
    dsm.registerSubscription("B", {0, 1, 2});
    dsm.registerSubscription("C", {0, 1});

    dsm.setCallback([&dsm, rank](std::string var, int oldVal, int newVal) {
        if (var == "A") local_A = newVal;
        if (var == "B") local_B = newVal;

        printf("[P%d] UPDATE: %s %d -> %d (Clock: %d)\n", 
               rank, var.c_str(), oldVal, newVal, dsm.getLamportClock());
    });

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << "[P0] (Coordinator A) Starting 2PC Write A=1" << std::endl;
        dsm.write("A", 1);
        std::cout << "[P0] Finished Write A=1" << std::endl;
    }
    else if (rank == 1) {
        while (local_A != 1) { std::this_thread::yield(); }
        std::cout << "[P1] Observed A=1. (Coordinator B) Starting 2PC Write B=1" << std::endl;
        dsm.write("B", 1);
    }
    else if (rank == 2) {
        while (local_B != 1) { std::this_thread::yield(); }
        
        int final_A = local_A;
        std::cout << "\n-------------------------------------------------\n";
        if (final_A == 1) {
            std::cout << "[P2] SUCCESS: Strong Consistency. A=1 seen before B=1.\n";
        } else {
            std::cout << "[P2] FAILURE: Saw B=1 but A is " << final_A << ".\n";
        }
        std::cout << "-------------------------------------------------\n" << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "[P2] Attempting CAS on A (1 -> 50)" << std::endl;
        
        bool res = dsm.compareAndExchange("A", 1, 50);
        std::cout << "[P2] CAS Result: " << (res ? "Success" : "Fail") << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    printf("[P%d] Exiting...\n", rank);
    return 0;
}