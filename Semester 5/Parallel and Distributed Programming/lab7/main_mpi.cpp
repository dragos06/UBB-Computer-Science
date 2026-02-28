#include <iostream>
#include <iomanip>
#include <chrono>
#include <mpi.h>
#include "PolynomialUtils.h"
#include "NaiveMultiplication.h"
#include "KaratsubaMultiplication.h"
#include "MpiPolyMultiplication.h"
#include "BigIntUtils.h"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const size_t POLY_SIZE = 10000;
    
    Polynomial P1, P2;
    if (rank == 0) {
        P1 = randomPoly(POLY_SIZE);
        P2 = randomPoly(POLY_SIZE);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    auto startNaive = std::chrono::high_resolution_clock::now();
    Polynomial r_mpi_naive = multiplyNaiveMPI(P1, P2, rank, size);
    MPI_Barrier(MPI_COMM_WORLD);
    auto endNaive = std::chrono::high_resolution_clock::now();
    
    if (rank == 0) {
        std::chrono::duration<double> diff = endNaive - startNaive;
        std::cout << "MPI Naive Time: " << diff.count() << " s" << std::endl;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    auto startKara = std::chrono::high_resolution_clock::now();
    Polynomial r_mpi_kara = multiplyKaratsubaMPI(P1, P2, rank, size);
    MPI_Barrier(MPI_COMM_WORLD);
    auto endKara = std::chrono::high_resolution_clock::now();

    if (rank == 0) {
        std::chrono::duration<double> diff = endKara - startKara;
        std::cout << "MPI Karatsuba Time: " << diff.count() << " s" << std::endl;
        
        std::cout << "\nVerifying against Sequential Lab 5...\n";
        
        auto startSeq = std::chrono::high_resolution_clock::now();
        Polynomial r_n_seq = multiplyNaiveSequential(P1, P2);
        auto endSeq = std::chrono::high_resolution_clock::now();
        std::cout << "Seq Naive Time: " << std::chrono::duration<double>(endSeq - startSeq).count() << " s" << std::endl;
        
        startSeq = std::chrono::high_resolution_clock::now();
        Polynomial r_k_seq = multiplyKaratsubaSequential(P1, P2);
        endSeq = std::chrono::high_resolution_clock::now();
        std::cout << "Seq Karatsuba Time: " << std::chrono::duration<double>(endSeq - startSeq).count() << " s" << std::endl;

        auto trim = [](Polynomial& p) { while(p.size() > 1 && p.back() == 0) p.pop_back(); };
        trim(r_mpi_naive); trim(r_mpi_kara); trim(r_k_seq);

        bool okNaive = areEqual(r_mpi_naive, r_k_seq);
        bool okKara = areEqual(r_mpi_kara, r_k_seq);

        if (okNaive && okKara) {
            std::cout << "SUCCESS: MPI results match sequential results." << std::endl;
        } else {
            std::cout << "FAILURE: Results differ." << std::endl;
            if (!okNaive) std::cout << "MPI Naive failed." << std::endl;
            if (!okKara) std::cout << "MPI Karatsuba failed." << std::endl;
        }
    }

    if (rank == 0) {
        normalizeBigInt(r_mpi_kara);
        std::cout << "Result (First 50 digits): " << bigIntToString(r_mpi_kara).substr(0, 50) << "..." << std::endl;
    }

    MPI_Finalize();
    return 0;
}