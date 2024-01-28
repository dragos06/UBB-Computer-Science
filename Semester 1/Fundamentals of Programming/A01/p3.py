# Solve the problem from the third set here

# PROBLEM 14 START
def is_prime(n: int) -> bool:
    if n <= 1:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True


def prime_factorization(n: int) -> int:
    sum_divs = 0
    divisor = 2
    while n > 1:
        power = 0
        while n % divisor == 0:
            n //= divisor
            power = 1
        if power:
            sum_divs += divisor
        divisor += 1
    return sum_divs


def prime_divisors(n: int) -> list:
    divs = []
    divisor = 2
    while n > 1:
        power = 0
        while n % divisor == 0:
            n //= divisor
            power += 1
        if power:
            divs.append(divisor)
        divisor += 1
    return divs


print(
    "14. Determine the n-th element of the sequence 1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,... obtained from the\n"
    "sequence of natural numbers by replacing composed numbers with their prime divisors, each divisor d being\n "
    "written d times, without memorizing the elements of the sequence.")
user_n = int(input("Please enter a natural number: "))
if user_n == 1:
    print("The n-th element of the sequence is: ", 1)
else:
    curr_num = 2
    index_pos = 1
    while True:
        if is_prime(curr_num):
            index_pos += 1
            if user_n == index_pos:
                print("The n-th element of the sequence is: ", curr_num)
                break
        else:
            nr_divs = prime_factorization(curr_num)
            if index_pos + nr_divs < user_n:
                index_pos += nr_divs
            else:
                rest = user_n - index_pos
                divs_set = prime_divisors(curr_num)
                ok = 0
                for div in divs_set:
                    if div - rest >= 0:
                        print("The n-th element of the sequence is: ", div)
                        ok = 1
                        break
                    else:
                        rest = rest - div
                if ok:
                    break
        curr_num += 1

# PROBLEM 14 END
print('\n\n')


# PROBLEM 15 START
def is_perfect(n: int) -> bool:
    if n == 1:
        return False
    sum_divs = 1
    i = 2
    while i * i <= n:
        if n % i == 0 and i != n / i:
            sum_divs += i + n / i
        elif n % i == 0:
            sum_divs += i
        i += 1
    if sum_divs == n:
        return True
    return False


def perfect_smaller_than(n: int) -> int:
    while n:
        if is_perfect(n):
            return n
        n -= 1


print(
    "15. Generate the largest perfect number smaller than a given natural number n. If such a number does not "
    "exist, a message should be displayed. A number is perfect if it is equal to the sum of its divisors, except "
    "itself.")
user_number = int(input("Please enter a natural number: "))
perfect_number = perfect_smaller_than(user_number - 1)
if perfect_number:
    print(f"The largest perfect number smaller than {user_number} is: ", perfect_number)
else:
    print(f"There is no perfect number smaller than {user_number}")
# PROBLEM 15 END
