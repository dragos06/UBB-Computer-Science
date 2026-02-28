#include <iostream>
#include <iomanip>
#include <chrono>
#include "PolynomialUtils.h"
#include "NaiveMultiplication.h"
#include "KaratsubaMultiplication.h"
#include "OpenCLMultiplication.h"

int main()
{
        const size_t POLY_SIZE = 10000;

        std::cout << "=== Polynomial Multiplication OpenCL Lab (Bonus) ===" << std::endl;
        std::cout << "Polynomial Degree: " << POLY_SIZE << std::endl;
        std::cout << "Initializing OpenCL..." << std::endl;
        initOpenCL();

        std::cout << "Generating random polynomials..." << std::endl;
        Polynomial P1 = randomPoly(POLY_SIZE);
        Polynomial P2 = randomPoly(POLY_SIZE);

        Polynomial r1, r2, r3, r4, r5, r6;
        double t1, t2, t3, t4, t5, t6;

        std::cout << std::fixed << std::setprecision(4);
        std::cout << "\nRunning Benchmarks...\n"
                  << std::endl;

        auto measure = [](auto func, const char *name, double &timeVar, Polynomial &res)
        {
                auto start = std::chrono::high_resolution_clock::now();
                res = func();
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> diff = end - start;
                timeVar = diff.count();
                std::cout << name << ": " << timeVar << " s" << std::endl;
        };

        measure([&]()
                { return multiplyNaiveSequential(P1, P2); },
                "1. CPU Naive Sequential    ", t1, r1);

        measure([&]()
                { return multiplyNaiveParallel(P1, P2); },
                "2. CPU Naive Parallel      ", t2, r2);

        measure([&]()
                { return multiplyKaratsubaSequential(P1, P2); },
                "3. CPU Karatsuba Sequential", t3, r3);

        measure([&]()
                { return multiplyKaratsubaParallel(P1, P2); },
                "4. CPU Karatsuba Parallel  ", t4, r4);

        measure([&]()
                { return multiplyOpenCLNaive(P1, P2); },
                "5. GPU Naive (OpenCL)      ", t5, r5);

        measure([&]()
                { return multiplyOpenCLKaratsuba(P1, P2); },
                "6. GPU Karatsuba (Hybrid)  ", t6, r6);

        std::cout << "\nVerifying Results..." << std::endl;

        auto trim = [](Polynomial &p)
        { while(p.size() > 1 && p.back() == 0) p.pop_back(); };
        trim(r1);
        trim(r5);
        trim(r6);

        bool okNaiveGPU = areEqual(r1, r5);
        bool okKaraGPU = areEqual(r1, r6);

        if (okNaiveGPU && okKaraGPU)
        {
                std::cout << "SUCCESS: All algorithms produced identical results." << std::endl;
        }
        else
        {
                std::cout << "FAILURE: Results differ!" << std::endl;
                std::cout << "GPU Naive: " << (okNaiveGPU ? "OK" : "FAIL") << std::endl;
                std::cout << "GPU Kara:  " << (okKaraGPU ? "OK" : "FAIL") << std::endl;
        }

        cleanupOpenCL();
        return 0;
}