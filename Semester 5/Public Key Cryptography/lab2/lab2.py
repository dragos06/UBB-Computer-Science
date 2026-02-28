# Strong Pseudoprime Base Finder
# n - strong pseudoprime to base b if:
#   n - 1 = 2^s * t
#   and either:
#       b^t = 1 (mod n)
#   or
#       b^((2^j) * t) = -1 (mod n)



# Compute GCD of two numbers
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

# Compute (base^exponent) % mod using repeated squaring
def modular_exponentiation(base, exponent, mod):
    result = 1
    base = base % mod
    while exponent > 0:
        if exponent % 2 == 1:
            result = (result * base) % mod
        exponent = exponent // 2
        base = (base * base) % mod
    return result

# Find all strong pseudoprime bases for a given n
def find_strong_pseudoprime_bases(n):
    '''
    For a given odd composite n, find all bases b (2 <= b <= n-2)
    such that n is a strong pseudoprime to base b.
    '''
    bases = []
    
    # write n - 1 = 2^s * t, where t is odd
    t = n - 1
    s = 0
    while t % 2 == 0:
        t = t // 2
        s = s + 1
    
    # test each possible base b
    for b in range(2, n-1):
        if gcd(b, n) != 1:
            continue # base must be coprime with n

        # compute b^t mod n using repeated squaring
        x = modular_exponentiation(b, t, n)

        # first condition: b^t = 1 (mod n)
        if x == 1:
            bases.append(b)
            continue

        # second condition: b^((2^j) * t) = -1 (mod n)
        for j in range(0, s):
            if x == n - 1:
                bases.append(b)
                break
            x = (x * x) % n # square and reduce mod n
    
    return bases

if __name__ == "__main__":
    print("=== Strong Pseudoprime Base Finder ===\n")
    
    test_numbers = [9, 15, 21, 25, 27, 33, 35, 45, 49, 561, 1105]
    
    for n in test_numbers:
        bases = find_strong_pseudoprime_bases(n)
        print(f"n = {n}")
        print(f"  Strong pseudoprime bases: {bases if bases else 'None'}\n")

    while True:
        user_input = input("Enter an odd composite number (or 'q' to quit): ")
        if user_input.lower() == 'q':
            break
        try:
            n = int(user_input)
            if n % 2 == 0 or n < 3:
                print("Please enter an odd composite number greater than 3.\n")
                continue
            bases = find_strong_pseudoprime_bases(n)
            print(f"Strong pseudoprime bases for n = {n}: {bases if bases else 'None'}\n")
        except ValueError:
            print("Invalid input. Please enter a number.\n")