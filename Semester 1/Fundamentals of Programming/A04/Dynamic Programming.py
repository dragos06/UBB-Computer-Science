def print_menu():
    print("Dynamic Programming:\n5. Maximize the profit when selling a rod of length n. The rod can be cut into pieces"
          "\n   of integer lengths and pieces can be sold individually. The prices are known for each possible length."
          "\n   For example, if rod length n = 7, and the price array is price = [1, 5, 8, 9, 10, 17, 17] "
          "\n   (the price of a piece of length 3 is 8), the maximum profit is 18, and is obtained by cutting the rod"
          "\n   into 3 pieces, two of length two and one of length 3. Display the profit and the length of rod sections"
          "\n   sold to obtain it.")
    print("\n\n")


def print_solution_dp(value_list: list, combination_list: list):
    print(f"The maximum profit is {value_list[len(value_list) - 1]}")
    print(f"The profit is obtained by cutting the rod into {len(combination_list[len(combination_list) - 1])} pieces:")
    set_combination_list = set(combination_list[len(combination_list) - 1])
    for numbers in set_combination_list:
        print(f"{combination_list[len(combination_list) - 1].count(numbers)} of length {numbers}")
    print("The data structure used to memorize the intermediate results is:")
    print(value_list)


def print_solution_naive(max_profit: int, best_solution: list):
    print(f"The maximum profit is {max_profit}")
    print(f"The profit is obtained by cutting the rod into {len(best_solution)} pieces:")
    set_best_solution = set(best_solution)
    for numbers in set_best_solution:
        print(f"{best_solution.count(numbers)} of length {numbers}")


def rod_naive(rod_length: int, price_list: list):
    if rod_length <= 0:
        return 0, []
    max_profit = -float('inf')
    best_solution = []
    for index in range(1, rod_length + 1):
        profit, solution = rod_naive(rod_length - index, price_list)
        current_profit = price_list[index - 1] + profit
        if current_profit > max_profit:
            max_profit = current_profit
            best_solution = [index] + solution
    return max_profit, best_solution


def rod_dp(rod_length: int, price_list: list):
    dp_array = [price_list[0]]
    gen_solution = [[] for _ in range(rod_length)]
    gen_solution[0] = [1]
    for index in range(1, rod_length):
        current_index_max = -1
        i = 0
        j = index - 1
        max_i = 0
        max_j = 0
        while i <= j:
            if dp_array[i] + dp_array[j] >= current_index_max:
                current_index_max = dp_array[i] + dp_array[j]
                max_i = i
                max_j = j
            i += 1
            j -= 1
        if current_index_max > price_list[index]:
            dp_array.append(current_index_max)
            for elements in gen_solution[max_i]:
                gen_solution[index].append(elements)
            for elements in gen_solution[max_j]:
                gen_solution[index].append(elements)
        else:
            dp_array.append(price_list[index])
            gen_solution[index] = [index + 1]
    print_solution_dp(dp_array, gen_solution)


def dp_user_input():
    rod_length = int(input("Please enter the length of the rod: "))
    print('\n')
    price_list = []
    for i in range(rod_length):
        price_list.append(int(input(f"Please enter the price of the rod cut into the length of {i}: ")))
    print("\nNaive Solution:\n")
    max_profit, best_solution = rod_naive(rod_length, price_list)
    print_solution_naive(max_profit, best_solution)
    print("\nDynamic Programming Solution:\n")
    rod_dp(rod_length, price_list)


dp_user_input()
