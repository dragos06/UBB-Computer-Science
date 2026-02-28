#ifndef KARATSUBA_MULTIPLICATION_H
#define KARATSUBA_MULTIPLICATION_H

#include "PolynomialUtils.h"

Polynomial multiplyKaratsubaSequential(const Polynomial& A, const Polynomial& B);
Polynomial multiplyKaratsubaParallel(const Polynomial& A, const Polynomial& B, int depth = 0);

#endif