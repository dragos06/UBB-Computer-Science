#ifndef OPENCL_MULTIPLICATION_H
#define OPENCL_MULTIPLICATION_H

#include "PolynomialUtils.h"

void initOpenCL();

void cleanupOpenCL();

Polynomial multiplyOpenCLNaive(const Polynomial &A, const Polynomial &B);

Polynomial multiplyOpenCLKaratsuba(const Polynomial &A, const Polynomial &B);

#endif