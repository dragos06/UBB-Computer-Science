def print_menu():
    print(
        "Backtracking:\n12. Consider the natural number n (n<=10) and the natural numbers a1, ..., an. Determine all"
        "\n     the possibilities to insert between all numbers a1, ..., an the operators + and – such that by"
        "\n     evaluating the expression the result is positive.")
    print("\n\n")


def print_sign(sign: int) -> str:
    if sign == 0:
        return '+'
    elif sign == 1:
        return '-'


def print_solution(sign_list: list, number_sequence: list):
    sign_index = 0
    print(number_sequence[0], end="")
    for number_index in range(1, len(number_sequence)):
        print(print_sign(sign_list[sign_index]), end="")
        print(number_sequence[number_index], end="")
        sign_index += 1
    print('=', end="")
    print(verify_solution(sign_list, number_sequence, len(number_sequence)))


def verify_solution(sign_list: list, number_sequence: list, index: int) -> int:
    result = number_sequence[0]
    sign_index = 0
    for number_index in range(1, index):
        if sign_list[sign_index] == 0:
            result = result + number_sequence[number_index]
        elif sign_list[sign_index] == 1:
            result = result - number_sequence[number_index]
        sign_index += 1
    return result


def consistency(index, number_sequence, sign_list):
    abs_sum = 0
    for i in range(index, len(number_sequence)):
        abs_sum += number_sequence[i]
    past_sum = verify_solution(sign_list, number_sequence, index)
    if past_sum < 0 and abs(past_sum) > abs_sum:
        return 1
    return 0


def solution_rec(sign_list, number_sequence):
    return len(sign_list) == len(number_sequence) - 1


def solution_iter(level, number_sequence):
    return level == len(number_sequence) - 1


def bkt_rec(sign_list: list, number_sequence: list):
    sign_list.append(0)
    for sign in range(2):
        sign_list[len(sign_list) - 1] = sign
        if solution_rec(sign_list, number_sequence):
            if verify_solution(sign_list, number_sequence, len(number_sequence)) >= 0:
                print_solution(sign_list, number_sequence)
        elif sign_list[len(sign_list) - 1] == 1:
            if consistency((len(sign_list) - 1) + 2, number_sequence, sign_list) == 0:
                bkt_rec(sign_list[:], number_sequence)
        else:
            bkt_rec(sign_list[:], number_sequence)


def bkt_iter(number_sequence: list):
    stack = []
    sign_list = [0] * (len(number_sequence) - 1)
    stack.append((sign_list, 0))
    while stack:
        sign_list, level = stack.pop()
        if solution_iter(level, number_sequence):
            if verify_solution(sign_list, number_sequence, len(number_sequence)) >= 0:
                print_solution(sign_list, number_sequence)
        elif sign_list[len(sign_list) - 1] == 1:
            if consistency((len(sign_list) - 1) + 2, number_sequence, sign_list) == 0:
                for sign in range(2):
                    sign_list[level] = sign
                    stack.append((sign_list[:], level + 1))
        else:
            for sign in range(2):
                sign_list[level] = sign
                stack.append((sign_list[:], level + 1))


def bkt_user_input():
    list_length = int(input("Please enter the length of the list: "))
    print('\n')
    user_list = []
    for i in range(list_length):
        user_list.append(int(input(f"Please enter element {i + 1}: ")))
    print("\nRecursive Backtracking:")
    bkt_rec([], user_list)
    print("\nIterative Backtracking:")
    bkt_iter(user_list)


print_menu()
bkt_user_input()
