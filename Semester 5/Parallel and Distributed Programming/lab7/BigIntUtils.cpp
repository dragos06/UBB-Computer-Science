#include "BigIntUtils.h"
#include <algorithm>

void normalizeBigInt(Polynomial& poly) {
    long long carry = 0;
    for (size_t i = 0; i < poly.size(); ++i) {
        poly[i] += carry;
        carry = poly[i] / 10;
        poly[i] %= 10;
    }
    
    while (carry > 0) {
        poly.push_back(carry % 10);
        carry /= 10;
    }
}

std::string bigIntToString(const Polynomial& poly) {
    if (poly.empty()) return "0";
    std::string s = "";
    for (size_t i = poly.size(); i > 0; --i) {
        s += std::to_string(poly[i-1]);
    }
    return s;
}