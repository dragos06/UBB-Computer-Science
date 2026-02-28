#include <iostream>
#include <iomanip>
#include <chrono>
#include "PolynomialUtils.h"
#include "NaiveMultiplication.h"
#include "KaratsubaMultiplication.h"

int main() {
    const size_t POLY_SIZE = 50000; 
    
    std::cout << "Polynomial Multiplication Lab" << std::endl;
    std::cout << "Polynomial Degree: " << POLY_SIZE << std::endl;
    std::cout << "Generating random polynomials..." << std::endl;

    Polynomial P1 = randomPoly(POLY_SIZE);
    Polynomial P2 = randomPoly(POLY_SIZE);

    Polynomial r1, r2, r3, r4;
    double t1, t2, t3, t4;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\nRunning Benchmarks...\n" << std::endl;

    // 1. Naive Sequential
    {
        auto start = std::chrono::high_resolution_clock::now();
        r1 = multiplyNaiveSequential(P1, P2);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        t1 = diff.count();
        std::cout << "1. Naive Sequential:    " << t1 << " s" << std::endl;
    }

    // 2. Naive Parallel
    {
        auto start = std::chrono::high_resolution_clock::now();
        r2 = multiplyNaiveParallel(P1, P2);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        t2 = diff.count();
        std::cout << "2. Naive Parallel:      " << t2 << " s" << std::endl;
    }

    // 3. Karatsuba Sequential
    {
        auto start = std::chrono::high_resolution_clock::now();
        r3 = multiplyKaratsubaSequential(P1, P2);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        t3 = diff.count();
        std::cout << "3. Karatsuba Sequential:" << t3 << " s" << std::endl;
    }

    // 4. Karatsuba Parallel
    {
        auto start = std::chrono::high_resolution_clock::now();
        r4 = multiplyKaratsubaParallel(P1, P2);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        t4 = diff.count();
        std::cout << "4. Karatsuba Parallel:  " << t4 << " s" << std::endl;
    }

    std::cout << "\nVerifying Results..." << std::endl;
    auto trim = [](Polynomial& p) { while(p.size() > 1 && p.back() == 0) p.pop_back(); };
    trim(r1); trim(r2); trim(r3); trim(r4);

    bool okNaive = areEqual(r1, r2);
    bool okKara = areEqual(r3, r4);
    bool okCross = areEqual(r1, r3);

    if (okNaive && okKara && okCross) {
        std::cout << "SUCCESS: All algorithms produced identical results." << std::endl;
    } else {
        std::cout << "FAILURE: Results differ!" << std::endl;
        std::cout << "Naive Seq vs Par: " << (okNaive ? "OK" : "FAIL") << std::endl;
        std::cout << "Kara Seq vs Par:  " << (okKara ? "OK" : "FAIL") << std::endl;
        std::cout << "Naive vs Kara:    " << (okCross ? "OK" : "FAIL") << std::endl;
    }

    return 0;
}