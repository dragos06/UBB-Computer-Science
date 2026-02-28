#include "PolynomialUtils.h"
#include <random>
#include <algorithm>

void printPoly(const Polynomial& poly, const std::string& name) {
    std::cout << name << ": [";
    for (size_t i = 0; i < poly.size(); ++i) {
        std::cout << poly[i] << (i < poly.size() - 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;
}

Polynomial randomPoly(size_t size) {
    Polynomial p(size);
    static std::mt19937 gen(42); 
    std::uniform_int_distribution<int> dis(0, 9);
    for (auto& coeff : p) {
        coeff = dis(gen);
    }
    return p;
}

bool areEqual(const Polynomial& a, const Polynomial& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void addPoly(Polynomial& res, const Polynomial& A, const Polynomial& B) {
    size_t n = std::max(A.size(), B.size());
    res.resize(n);
    for (size_t i = 0; i < n; ++i) {
        long long aVal = (i < A.size()) ? A[i] : 0;
        long long bVal = (i < B.size()) ? B[i] : 0;
        res[i] = aVal + bVal;
    }
}