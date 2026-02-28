"""
This program implements and compares three algorithms for computing
the Greatest Common Divisor (GCD) of two natural numbers:
    1. Euclidean Algorithm (division-based)
    2. Subtraction-based Algorithm
    3. Prime Factorization Algorithm
"""

import time
import random

# Algorithm 1: Classical Euclidean Algorithm (division-based)
def gcd_euclidean(a, b):
    """
    Compute GCD using the classical Euclidean algorithm.

    Idea:
      The remainder-based Euclidean algorithm repeatedly replaces the
      larger number by the remainder of dividing it by the smaller number
      until the remainder becomes zero. The non-zero value at that point
      is the GCD.

    Time complexity: O(log(min(a, b)))
    """
    while b != 0:
        a, b = b, a % b   # Replace (a, b) with (b, a mod b)
    return a


# Algorithm 2: Subtraction-based Euclidean Algorithm
def gcd_subtraction(a, b):
    """
    Compute GCD using repeated subtraction.

    Idea:
      Subtract the smaller number from the larger number repeatedly
      until both become equal. The resulting number is the GCD.

    This method is conceptually simple but inefficient for large numbers
    because it requires many iterations.

    Time complexity: O(max(a, b))
    """
    while a != b:
        if a > b:
            a -= b   # Reduce the larger number
        else:
            b -= a
    return a


# Algorithm 3: Prime Factorization Algorithm
def prime_factors(n):
    """
    Return a dictionary of prime factors of n and their powers.

    Example:
        n = 60 = 2^2 * 3^1 * 5^1
        -> {2: 2, 3: 1, 5: 1}

    Method:
      - Divide n by 2 until it’s odd.
      - Then test all odd divisors from 3 up to sqrt(n).
      - Remaining n > 2 (if any) is a prime factor.
    """
    factors = {}

    # Handle the factor 2 separately
    while n % 2 == 0:
        factors[2] = factors.get(2, 0) + 1
        n //= 2

    # Handle odd factors
    i = 3
    while i * i <= n:
        while n % i == 0:
            factors[i] = factors.get(i, 0) + 1
            n //= i
        i += 2

    # If n is now greater than 2, it is a prime number
    if n > 2:
        factors[n] = factors.get(n, 0) + 1

    return factors


def gcd_prime_factorization(a, b):
    """
    Compute GCD using the prime factorization method.

    Idea:
      - Find the prime factors of both a and b.
      - Multiply all primes that appear in both factorizations,
        raised to the power of their minimum exponents.

    Example:
        a = 60 = 2^2 * 3^1 * 5^1
        b = 90 = 2^1 * 3^2 * 5^1
        GCD = 2^1 * 3^1 * 5^1 = 30

    Time complexity: Depends on factorization (~O(sqrt(n)) per number)
    """
    fa = prime_factors(a)
    fb = prime_factors(b)

    gcd_val = 1
    # Multiply common prime factors to the lowest power
    for p in fa.keys() & fb.keys():
        gcd_val *= p ** min(fa[p], fb[p])
    return gcd_val


# Helper Function: Measure Execution Time
def measure_time(func, a, b):
    """
    Measure execution time of a GCD function in microseconds.

    Parameters:
        func: The GCD function to test.
        a, b: Input numbers.

    Returns:
        (result, elapsed_time_microseconds)
    """
    start = time.perf_counter_ns()  # High-resolution start time
    result = func(a, b)
    end = time.perf_counter_ns()    # End time

    elapsed_us = (end - start) / 1000.0  # Convert ns → µs
    return result, elapsed_us


# Main Section: Run and Compare Algorithms
if __name__ == "__main__":
    print("Comparative Running-Time Analysis of GCD Algorithms\n")
    print(f"{'A':>8} {'B':>8} {'Euclid(µs)':>12} {'Subtraction(µs)':>18} {'PrimeFact(µs)':>15} {'Euclid Res':>12} {'Subtraction Res':>18} {'PrimeFact Res':>15}")

    # Generate 10 random test pairs (within a manageable range)
    test_inputs = [(random.randint(1000000, 100000000), random.randint(1000000, 100000000)) for _ in range(10)]

    # Compare runtime for each pair of inputs
    for a, b in test_inputs:
        r1, t1 = measure_time(gcd_euclidean, a, b)
        r2, t2 = measure_time(gcd_subtraction, a, b)
        r3, t3 = measure_time(gcd_prime_factorization, a, b)

        # Display formatted results for each test
        print(f"{a:8d} {b:8d} {t1:12.3f} {t2:18.3f} {t3:15.3f} {r1:12.3f} {r2:18.3f} {r3:15.3f}")
