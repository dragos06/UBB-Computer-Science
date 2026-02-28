#ifndef BIG_INT_UTILS_H
#define BIG_INT_UTILS_H

#include "PolynomialUtils.h"
#include <string>

void normalizeBigInt(Polynomial& poly);

std::string bigIntToString(const Polynomial& poly);

#endif