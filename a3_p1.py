import time


def print_menu():
    print(100 * "_")
    print("Sorting Application:\n")
    print("1. Choose the length of the randomly generated list. Generated numbers will be between 0 and 100.")
    print("2. Use Cocktail Sort.")
    print("3. Use Comb Sort.")
    print("4. Timing of the sorting algorithms for the best case scenario")
    print("5. Timing of the sorting algorithms for the worst case scenario")
    print("6. Timing of the sorting algorithms for the average case scenario")
    print("7. Exit the program.")
    print(100 * '_')


def copy_user_list(input_list: list) -> list:
    copy_list = []
    for element in input_list:
        copy_list.append(element)
    return copy_list


def read_step_value() -> int:
    step = input("Please enter the value of step: ")
    while not step.isnumeric() or step == 0:
        step = input("Please enter a valid value: ")
    return int(step)


def create_best_case(to_sort_list: list) -> list:
    to_sort_list.sort()
    return to_sort_list


def create_worst_case(to_sort_list: list) -> list:
    to_sort_list.sort(reverse=True)
    return to_sort_list


def option1_input_length() -> list:
    list_length = input("Please enter the length of the list: ")
    while not list_length.isnumeric() or int(list_length) <= 0:
        list_length = input("Please enter a valid value: ")
    import random
    random_list = []
    list_length = int(list_length)
    for i in range(list_length):
        random_list.append(random.randint(0, 100))
    print(f"The randomly generated list of length {list_length} is: \n", random_list)
    return random_list


def random_list_generator() -> list:
    list_length = input("Please enter the length of the list: ")
    while not list_length.isnumeric() or int(list_length) <= 0:
        list_length = input("Please enter a valid value: ")
    import random
    random_list = []
    list_length = int(list_length)
    for i in range(16 * list_length):
        random_list.append(random.randint(0, 10000))
    return random_list


def comb_time_sort(used_list: list) -> float:
    start = time.perf_counter()
    option3_comb_sort_no_step(used_list)
    return time.perf_counter() - start


def cocktail_time_sort(used_list: list) -> float:
    start = time.perf_counter()
    option2_cocktail_sort_no_step(used_list)
    return time.perf_counter() - start


def option2_cocktail_sort(random_list, step) -> list:
    copy_step = step
    list_length = len(random_list)
    left = 0
    right = list_length - 1
    swap = True
    while swap:
        swap = False
        for i in range(left, right):
            if random_list[i] > random_list[i + 1]:
                aux = random_list[i]
                random_list[i] = random_list[i + 1]
                random_list[i + 1] = aux
                swap = True
                copy_step -= 1
            if copy_step == 0:
                print(random_list)
                copy_step = step
        if not swap:
            break

        swap = False
        right -= 1
        for i in range(right - 1, left - 1, -1):
            if random_list[i] > random_list[i + 1]:
                aux = random_list[i]
                random_list[i] = random_list[i + 1]
                random_list[i + 1] = aux
                swap = True
                copy_step -= 1
            if not copy_step:
                print(random_list)
                copy_step = step
        left += 1
    return random_list


def option2_cocktail_sort_no_step(random_list) -> list:
    list_length = len(random_list)
    left = 0
    right = list_length - 1
    swap = True
    while swap:
        swap = False
        for i in range(left, right):
            if random_list[i] > random_list[i + 1]:
                aux = random_list[i]
                random_list[i] = random_list[i + 1]
                random_list[i + 1] = aux
                swap = True
        if not swap:
            break

        swap = False
        right -= 1
        for i in range(right - 1, left - 1, -1):
            if random_list[i] > random_list[i + 1]:
                aux = random_list[i]
                random_list[i] = random_list[i + 1]
                random_list[i + 1] = aux
                swap = True
        left += 1
    return random_list


def next_gap(gap: int) -> int:
    gap = gap * 10 // 13
    if gap < 1:
        return 1
    return gap


def option3_comb_sort(random_list: list, step: int) -> list:
    n = len(random_list)
    gap = n
    swap = True
    copy_step = step
    while not gap == 1 or swap:
        gap = next_gap(gap)
        swap = False
        for i in range(n - gap):
            if random_list[i] > random_list[i + gap]:
                aux = random_list[i]
                random_list[i] = random_list[i + gap]
                random_list[i + gap] = aux
                swap = True
                copy_step -= 1
            if not copy_step:
                print(random_list)
                copy_step = step
    return random_list


def option3_comb_sort_no_step(random_list: list) -> list:
    n = len(random_list)
    gap = n
    swap = True
    while not gap == 1 or swap:
        gap = next_gap(gap)
        swap = False
        for i in range(n - gap):
            if random_list[i] > random_list[i + gap]:
                random_list[i], random_list[i + gap] = random_list[i + gap], random_list[i]
                swap = True
    return random_list


def option4_best_case_timing():
    to_be_sorted_list = random_list_generator()
    best_list = create_best_case(to_be_sorted_list)
    partial_list = []
    print('Time Table of the sorting algorithms in the best case possible:')
    print(23 * '_')
    print("Cocktail", " |   ", "Comb")
    print(23 * '_')
    nr = 0
    for i in best_list:
        partial_list.append(i)
        nr += 1
        if nr == len(best_list) // 16:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(best_list) // 8:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(best_list) // 4:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(best_list) // 2:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(best_list):
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')


def option5_worst_case_timing():
    to_be_sorted_list = random_list_generator()
    worst_list = create_worst_case(to_be_sorted_list)
    partial_list = []
    print('Time Table of the sorting algorithms in the worst case possible:')
    print(23 * '_')
    print("Cocktail", " |   ", "Comb")
    print(23 * '_')
    nr = 0
    for i in worst_list:
        partial_list.append(i)
        nr += 1
        if nr == len(worst_list) // 16:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(worst_list) // 8:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(worst_list) // 4:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(worst_list) // 2:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(worst_list):
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')


def option6_average_case_timing():
    to_be_sorted_list = random_list_generator()
    partial_list = []
    print('Time Table of the sorting algorithms in the average case:')
    print(23 * '_')
    print("Cocktail", " |   ", "Comb")
    print(23 * '_')
    nr = 0
    for i in to_be_sorted_list:
        partial_list.append(i)
        nr += 1
        if nr == len(to_be_sorted_list) // 16:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(to_be_sorted_list) // 8:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(to_be_sorted_list) // 4:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(to_be_sorted_list) // 2:
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')
        if nr == len(to_be_sorted_list):
            copy_list1 = copy_user_list(partial_list)
            copy_list2 = copy_user_list(partial_list)
            print('%.5f' % cocktail_time_sort(copy_list1), '  |  ', '%.5f' % comb_time_sort(copy_list2))
            print(23 * '_')


def user_input():
    user_random_list = []
    while True:
        user_choice = int(input("Please choose an option: "))
        while user_choice not in [1, 2, 3, 4, 5, 6, 7]:
            user_choice = int(input("Please enter a valid option: "))
        if user_choice == 1:
            user_random_list = option1_input_length()
        copy_random_list = copy_user_list(user_random_list)
        if user_choice == 2:
            if len(user_random_list) == 0:
                print("The list is empty. Please enter first the length of the list.")
                continue
            step_value = read_step_value()
            sorted_list = option2_cocktail_sort(copy_random_list, step_value)
            print(sorted_list)
        if user_choice == 3:
            if len(user_random_list) == 0:
                print("The list is empty. Please enter first the length of the list.")
                continue
            step_value = read_step_value()
            sorted_list = option3_comb_sort(copy_random_list, step_value)
            print(sorted_list)
        if user_choice == 4:
            option4_best_case_timing()
        if user_choice == 5:
            option5_worst_case_timing()
        if user_choice == 6:
            option6_average_case_timing()
        if user_choice == 7:
            print("Exiting...")
            break


print_menu()
user_input()
