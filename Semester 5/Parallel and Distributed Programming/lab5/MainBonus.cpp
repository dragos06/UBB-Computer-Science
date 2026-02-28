#include <iostream>
#include <iomanip>
#include <chrono>
#include "PolynomialUtils.h"
#include "NaiveMultiplication.h"
#include "KaratsubaMultiplication.h"
#include "BigIntUtils.h"

int main() {
    const size_t NUM_DIGITS = 3; 
    
    std::cout << "=== Big Number Multiplication Bonus ===" << std::endl;
    std::cout << "Number of Digits: " << NUM_DIGITS << std::endl;
    std::cout << "Generating random Big Integers..." << std::endl;

    Polynomial BigNum1 = randomPoly(NUM_DIGITS);
    Polynomial BigNum2 = randomPoly(NUM_DIGITS);

    Polynomial r1, r2, r3, r4;
    double t1, t2, t3, t4;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\nRunning Benchmarks (Multiplication + Carry Propagation)...\n" << std::endl;

    auto measure = [&](auto func, Polynomial& result, const std::string& name) {
        auto start = std::chrono::high_resolution_clock::now();
        
        result = func(BigNum1, BigNum2);
        std::cout<<bigIntToString(r1)<<std::endl;
        normalizeBigInt(result);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << name << ": " << diff.count() << " s" << std::endl;
        return diff.count();
    };

    t1 = measure(multiplyNaiveSequential, r1, "1. Naive Sequential    ");

    t2 = measure(multiplyNaiveParallel, r2, "2. Naive Parallel      ");

    t3 = measure(multiplyKaratsubaSequential, r3, "3. Karatsuba Sequential");

    auto runKaraPar = [](const Polynomial& A, const Polynomial& B) {
        return multiplyKaratsubaParallel(A, B); 
    };
    t4 = measure(runKaraPar, r4, "4. Karatsuba Parallel  ");

    std::cout << "\nVerifying Results..." << std::endl;
    
    auto trim = [](Polynomial& p) { while(p.size() > 1 && p.back() == 0) p.pop_back(); };
    trim(r1); trim(r2); trim(r3); trim(r4);

    bool okNaive = areEqual(r1, r2);
    bool okKara = areEqual(r3, r4);
    bool okCross = areEqual(r1, r3);

    if (okNaive && okKara && okCross) {
        std::cout << "SUCCESS: All algorithms produced identical Big Integers." << std::endl;
        std::cout << bigIntToString(BigNum1) << std::endl;
        std::cout << bigIntToString(BigNum2) << std::endl;
        std::cout<<bigIntToString(r1)<<std::endl;
    } else {
        std::cout << "FAILURE: Results differ!" << std::endl;
    }

    return 0;
}