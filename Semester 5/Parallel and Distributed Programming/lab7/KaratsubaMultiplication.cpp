#include "KaratsubaMultiplication.h"
#include "NaiveMultiplication.h"
#include <thread>
#include <vector>
#include <algorithm>

Polynomial multiplyKaratsubaSequential(const Polynomial& A, const Polynomial& B) {
    size_t n = A.size();
    // if (n == 0) return {}; 
    // if (n == 1) return {A[0] * B[0]};
    if (n <= 32) return multiplyNaiveSequential(A, B);

    size_t k = n / 2;

    Polynomial A0(A.begin(), A.begin() + k);
    Polynomial A1(A.begin() + k, A.end());
    Polynomial B0(B.begin(), B.begin() + k);
    Polynomial B1(B.begin() + k, B.end());

    Polynomial A0B0 = multiplyKaratsubaSequential(A0, B0);
    Polynomial A1B1 = multiplyKaratsubaSequential(A1, B1);
    
    Polynomial sumA; addPoly(sumA, A0, A1);
    Polynomial sumB; addPoly(sumB, B0, B1);
    Polynomial Mid = multiplyKaratsubaSequential(sumA, sumB);

    Polynomial result(2 * n - 1, 0); 
    
    for(size_t i=0; i<A0B0.size(); ++i) result[i] += A0B0[i];

    for(size_t i=0; i<A1B1.size(); ++i) {
        if (i + 2*k < result.size()) result[i + 2*k] += A1B1[i];
        else result.push_back(A1B1[i]);
    }

    for(size_t i=0; i<Mid.size(); ++i) {
        long long val = Mid[i];
        if (i < A0B0.size()) val -= A0B0[i];
        if (i < A1B1.size()) val -= A1B1[i];
        
        if (i + k < result.size()) result[i + k] += val;
        else result.push_back(val);
    }
    return result;
}

Polynomial multiplyKaratsubaParallel(const Polynomial& A, const Polynomial& B, int depth) {
    size_t n = A.size();

    if (n <= 32) return multiplyNaiveSequential(A, B);


    if (depth > 4) {
        return multiplyKaratsubaSequential(A, B);
    }

    size_t k = n / 2;

    Polynomial A0(A.begin(), A.begin() + k);
    Polynomial A1(A.begin() + k, A.end());
    Polynomial B0(B.begin(), B.begin() + k);
    Polynomial B1(B.begin() + k, B.end());

    Polynomial A0B0, A1B1, Mid;
    std::vector<std::thread> threads;

    threads.emplace_back([&]() { 
        A0B0 = multiplyKaratsubaParallel(A0, B0, depth + 1); 
    });

    threads.emplace_back([&]() { 
        A1B1 = multiplyKaratsubaParallel(A1, B1, depth + 1); 
    });
    
    Polynomial sumA; addPoly(sumA, A0, A1);
    Polynomial sumB; addPoly(sumB, B0, B1);
    
    threads.emplace_back([&]() { 
        Mid = multiplyKaratsubaParallel(sumA, sumB, depth + 1); 
    });

    for(auto& t : threads) {
        if(t.joinable()) t.join();
    }

    Polynomial result(A.size() + B.size(), 0); 
    if (result.size() > 0) result.pop_back(); 

    for(size_t i=0; i<A0B0.size(); ++i) {
        if(i < result.size()) result[i] += A0B0[i];
    }

    for(size_t i=0; i<A1B1.size(); ++i) {
        if(i + 2*k < result.size()) result[i + 2*k] += A1B1[i];
    }

    for(size_t i=0; i<Mid.size(); ++i) {
        long long val = Mid[i];
        if (i < A0B0.size()) val -= A0B0[i];
        if (i < A1B1.size()) val -= A1B1[i];
        if(i + k < result.size()) result[i + k] += val;
    }
    
    while(result.size() > 1 && result.back() == 0) result.pop_back();

    return result;
}