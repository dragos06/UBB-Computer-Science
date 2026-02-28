#ifndef NAIVE_MULTIPLICATION_H
#define NAIVE_MULTIPLICATION_H

#include "PolynomialUtils.h"

Polynomial multiplyNaiveSequential(const Polynomial& A, const Polynomial& B);
Polynomial multiplyNaiveParallel(const Polynomial& A, const Polynomial& B);

#endif