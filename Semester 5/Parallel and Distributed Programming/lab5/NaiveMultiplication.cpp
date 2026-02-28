#include "NaiveMultiplication.h"
#include <thread>
#include <vector>
#include <algorithm>

Polynomial multiplyNaiveSequential(const Polynomial& A, const Polynomial& B) {
    if (A.empty() || B.empty()) return {};
    size_t n = A.size();
    size_t m = B.size();
    Polynomial result(n + m - 1, 0);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            result[i + j] += A[i] * B[j];
        }
    }
    return result;
}

Polynomial multiplyNaiveParallel(const Polynomial& A, const Polynomial& B) {
    if (A.empty() || B.empty()) return {};
    size_t n = A.size();
    size_t m = B.size();
    size_t resultSize = n + m - 1;
    Polynomial result(resultSize, 0);

    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) numThreads = 4;
    
    std::vector<std::thread> threads;

    auto computeRange = [&](size_t start, size_t end) {
        for (size_t k = start; k < end; ++k) {
            long long sum = 0;
            size_t i_min = (k >= m) ? (k - m + 1) : 0;
            size_t i_max = std::min(k, n - 1);

            for (size_t i = i_min; i <= i_max; ++i) {
                sum += A[i] * B[k - i];
            }
            result[k] = sum;
        }
    };

    size_t chunkSize = (resultSize + numThreads - 1) / numThreads;
    for (size_t t = 0; t < numThreads; ++t) {
        size_t start = t * chunkSize;
        size_t end = std::min(start + chunkSize, resultSize);
        if (start < end) {
            threads.emplace_back(computeRange, start, end);
        }
    }

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    return result;
}