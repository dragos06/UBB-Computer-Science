#ifndef POLYNOMIAL_UTILS_H
#define POLYNOMIAL_UTILS_H

#include <vector>
#include <string>
#include <iostream>

typedef std::vector<long long> Polynomial;

void printPoly(const Polynomial& poly, const std::string& name);
Polynomial randomPoly(size_t size);
bool areEqual(const Polynomial& a, const Polynomial& b);

void addPoly(Polynomial& res, const Polynomial& A, const Polynomial& B);

#endif