# Solve the problem from the first set here

# PROBLEM 1 START
def is_prime(n: int) -> bool:
    if n <= 1:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True


def prime_larger_than(n: int) -> int:
    while not is_prime(n):
        n += 1
    return n


print("1. Generate the first prime number larger than a given natural number n.")
user_number = int(input("Please enter a natural number: "))
print("The first prime number larger than the given natural number n is: ", prime_larger_than(user_number + 1))
# PROBLEM 1 END
print("\n\n")


# PROBLEM 3 START
def extract_digits(n: int) -> list:
    digit_list = []
    while n > 0:
        digit_list.append(n % 10)
        n = int(n / 10)
    return digit_list


def smallest_same_digits(n: list) -> int:
    n.sort()
    m = 0
    for digits in n:
        if not digits == 0:
            m = m * 10 + digits
            n.remove(digits)
            break
    for digits in n:
        m = m * 10 + digits
    return m


print("3. For a given natural number n find the minimal natural number m formed with the same digits.")
user_number = int(input("Please enter a natural number: "))
user_digit_list = extract_digits(user_number)
print("The minimal natural number m formed with the same digits is: ", smallest_same_digits(user_digit_list))

# PROBLEM 3 END
print('\n\n')


# PROBLEM 4 START
def largest_same_digits(n: list) -> int:
    n.sort(reverse=True)
    m = 0
    for digits in n:
        m = m * 10 + digits
    return m


print("4. For a given natural number n find the largest natural number written with the same digits.")
user_number = int(input("Please enter a natural number: "))
user_digit_list = extract_digits(user_number)
print("The largest natural number m formed with the same digits is: ", largest_same_digits(user_digit_list))

# PROBLEM 4 END
print('\n\n')


# PROBLEM 5 START
def prime_smaller_than(n: int) -> int:
    while not is_prime(n) and n:
        n -= 1
    return n


print(
    "5. Generate the largest prime number smaller than a given natural number n. If such a number does not exist, a message should be displayed.")
user_number = int(input("Please enter a natural number: "))
prime_number = prime_smaller_than(user_number - 1)
if prime_number:
    print(f"The largest prime number smaller than {user_number} is: ", prime_number)
else:
    print(f"There is no prime number smaller than {user_number}")
# PROBLEM 5 END
