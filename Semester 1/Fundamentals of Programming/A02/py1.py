def print_menu():
    print(100 * "_")
    print("Sorting Application:\n")
    print("1. Choose the length of the randomly generated list. Generated numbers will be between 0 and 100.")
    print("2. Use Cocktail Sort.")
    print("3. Use Comb Sort.")
    print("4. Exit the program.")
    print(100 * '_')


def read_step_value() -> int:
    step = input("Please enter the value of step: ")
    while not step.isnumeric() or step == 0:
        step = input("Please enter a valid value: ")
    return int(step)


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


def copy_user_list(input_list: list) -> list:
    copy_list = []
    for element in input_list:
        copy_list.append(element)
    return copy_list


def user_input():
    user_random_list = []
    while True:
        user_choice = int(input("Please choose an option: "))
        while user_choice not in [1, 2, 3, 4]:
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
            print("Exiting...")
            break


print_menu()
user_input()
