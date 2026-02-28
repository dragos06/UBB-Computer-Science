#include "MpiPolyMultiplication.h"
#include "KaratsubaMultiplication.h"
#include "NaiveMultiplication.h"
#include <vector>
#include <algorithm>
#include <iostream>

void sendPoly(const Polynomial& p, int dest, int tag) {
    size_t size = p.size();
    MPI_Send(&size, 1, MPI_UNSIGNED_LONG, dest, tag, MPI_COMM_WORLD);
    MPI_Send(p.data(), size, MPI_LONG_LONG, dest, tag, MPI_COMM_WORLD);
}

Polynomial recvPoly(int source, int tag) {
    size_t size;
    MPI_Recv(&size, 1, MPI_UNSIGNED_LONG, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    Polynomial p(size);
    MPI_Recv(p.data(), size, MPI_LONG_LONG, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    return p;
}

Polynomial multiplyNaiveMPI(const Polynomial& A, const Polynomial& B, int rank, int worldSize) {
    size_t n = 0, m = 0;

    if (rank == 0) {
        n = A.size();
        m = B.size();
    }
    MPI_Bcast(&n, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&m, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

    Polynomial localA = (rank == 0) ? A : Polynomial(n);
    Polynomial localB = (rank == 0) ? B : Polynomial(m);

    MPI_Bcast(localA.data(), n, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(localB.data(), m, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    size_t resultSize = n + m - 1;
    
    size_t start = (rank * resultSize) / worldSize;
    size_t end = ((rank + 1) * resultSize) / worldSize;
    size_t localSize = end - start;

    std::vector<long long> localResult(localSize, 0);

    for (size_t k = start; k < end; ++k) {
        long long sum = 0;
        size_t i_min = (k >= m) ? (k - m + 1) : 0;
        size_t i_max = std::min(k, n - 1);

        for (size_t i = i_min; i <= i_max; ++i) {
            sum += localA[i] * localB[k - i];
        }
        localResult[k - start] = sum;
    }

    Polynomial finalResult;
    std::vector<int> counts(worldSize);
    std::vector<int> displs(worldSize);

    if (rank == 0) finalResult.resize(resultSize);

    for (int r = 0; r < worldSize; ++r) {
        size_t r_start = (r * resultSize) / worldSize;
        size_t r_end = ((r + 1) * resultSize) / worldSize;
        counts[r] = r_end - r_start;
        displs[r] = r_start;
    }

    MPI_Gatherv(localResult.data(), localSize, MPI_LONG_LONG,
                finalResult.data(), counts.data(), displs.data(), MPI_LONG_LONG,
                0, MPI_COMM_WORLD);

    return finalResult;
}

Polynomial multiplyKaratsubaMPI(const Polynomial& A, const Polynomial& B, int rank, int worldSize) {
    if (worldSize < 4) {
        if (rank == 0) return multiplyKaratsubaSequential(A, B);
        return {};
    }

    const int TAG_WORK = 1;
    const int TAG_RESULT = 2;

    if (rank == 0) {
        size_t n = A.size();
        size_t k = n / 2;

        Polynomial A0(A.begin(), A.begin() + k);
        Polynomial A1(A.begin() + k, A.end());
        Polynomial B0(B.begin(), B.begin() + k);
        Polynomial B1(B.begin() + k, B.end());

        Polynomial SumA; addPoly(SumA, A0, A1);
        Polynomial SumB; addPoly(SumB, B0, B1);

        sendPoly(A0, 1, TAG_WORK); sendPoly(B0, 1, TAG_WORK);
        sendPoly(A1, 2, TAG_WORK); sendPoly(B1, 2, TAG_WORK);
        sendPoly(SumA, 3, TAG_WORK); sendPoly(SumB, 3, TAG_WORK);

        Polynomial A0B0 = recvPoly(1, TAG_RESULT);
        Polynomial A1B1 = recvPoly(2, TAG_RESULT);
        Polynomial Mid  = recvPoly(3, TAG_RESULT);

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

    } else if (rank <= 3) {
        Polynomial pA = recvPoly(0, TAG_WORK);
        Polynomial pB = recvPoly(0, TAG_WORK);

        Polynomial res = multiplyKaratsubaSequential(pA, pB);

        sendPoly(res, 0, TAG_RESULT);
        return {};
    } else {
        return {};
    }
}