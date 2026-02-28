import math

MAX_K = 1000

def generalized_fermat(n, B):
    """
    Generalized Fermat factorization algorithm.
    Tries k = 1, 2, 3, ... up to MAX_K
    and searches for integers t, s such that t^2 - k*n = s^2.
    """
    for k in range(1, MAX_K):
        # Start t slightly above sqrt(k*n)
        t0 = math.isqrt(k*n)
        for t in range(t0 + 1, t0 + B + 1):
            s2 = t*t - k*n
            if s2 < 0:
                continue

            s = math.isqrt(s2)
            # Check if s2 is a perfect square
            if s*s == s2:
                # Print factorization formula
                print(f"n = 1/{k} * {(t+s)} * {(t-s)}")
                return

if __name__ == "__main__":
    n = int(input("Enter n to factor: "))
    B = int(input("Enter bound B for t search: "))
    generalized_fermat(n, B)
