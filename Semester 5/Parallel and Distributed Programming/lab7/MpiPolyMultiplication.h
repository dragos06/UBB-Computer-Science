#ifndef MPI_POLY_MULTIPLICATION_H
#define MPI_POLY_MULTIPLICATION_H

#include "PolynomialUtils.h"
#include <mpi.h>

Polynomial multiplyNaiveMPI(const Polynomial& A, const Polynomial& B, int rank, int worldSize);

Polynomial multiplyKaratsubaMPI(const Polynomial& A, const Polynomial& B, int rank, int worldSize);

#endif