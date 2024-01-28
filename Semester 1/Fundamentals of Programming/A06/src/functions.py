#
# The program's functions are implemented here. There is no user interaction in this file, therefore no input/print
# statements. Functions here communicate via function parameters, the return statement and raising of exceptions.
#
import random


def extract_a_b_from_string(complex_str: str) -> dict:
    """
    Extracts a and b from a+bi complex number and creates a dictionary containing the real part and imaginary part of
    said complex number
    :param complex_str: A string representing a complex number
    :return: A dictionary containing the real_part and imaginary_part of complex number
    """
    real_part = ''
    imaginary_part = ''
    count_plus = complex_str.count('+')
    count_minus = complex_str.count('-')
    if count_plus + count_minus == 2:
        plus_index = complex_str.find('+', 1)
        minus_index = complex_str.find('-', 1)
        if plus_index != -1:
            for index in range(plus_index):
                real_part += complex_str[index]
            for index in range(plus_index, len(complex_str)):
                imaginary_part += complex_str[index]
        elif minus_index != -1:
            for index in range(minus_index):
                real_part += complex_str[index]
            for index in range(minus_index, len(complex_str)):
                imaginary_part += complex_str[index]
    elif count_plus + count_minus == 1:
        if 'i' not in complex_str:
            real_part += complex_str
        else:
            if complex_str[0] == '-':
                imaginary_part += complex_str
            else:
                plus_index = complex_str.find('+', 0)
                minus_index = complex_str.find('-', 0)
                if plus_index != -1:
                    for index in range(plus_index):
                        real_part += complex_str[index]
                    for index in range(plus_index, len(complex_str)):
                        imaginary_part += complex_str[index]
                elif minus_index != -1:
                    for index in range(minus_index):
                        real_part += complex_str[index]
                    for index in range(minus_index, len(complex_str)):
                        imaginary_part += complex_str[index]
    elif count_plus + count_minus == 0:
        if 'i' in complex_str:
            imaginary_part += complex_str
        else:
            real_part += complex_str
    # if imaginary_part == '-i':
    #     imaginary_part = '-1'
    # elif imaginary_part == '+i' or imaginary_part == 'i':
    #     imaginary_part = '1'
    imaginary_part = imaginary_part.replace('i', '')
    if not imaginary_part:
        imaginary_part = '0'
    if not real_part:
        real_part = '0'
    if real_part[0] == '-' or real_part[0] == '+':
        if not real_part[1:].isnumeric():
            raise ValueError("Invalid complex number")
    elif imaginary_part[0] == '-' or imaginary_part[0] == '+':
        if not imaginary_part[1:].isnumeric():
            raise ValueError("Invalid complex number")
    else:
        if not imaginary_part.isnumeric() or not real_part.isnumeric():
            raise ValueError("Invalid complex number")
    return create_complex_number(int(real_part), int(imaginary_part))


def start_up() -> list:
    """
    Creates a random list of 10 complex numbers to be used at the start of the program
    :return: A list of 10 randomly generated complex numbers
    """
    start_up_list = []
    for i in range(10):
        real_part = random.randint(0, 20)
        imaginary_part = random.randint(0, 20)
        start_up_list.append(create_complex_number(real_part, imaginary_part))
    return start_up_list


def set_complex_number(real_part: int, imaginary_part: int) -> str:
    """
    Combines the real part and imaginary part of a complex number into one string and returns it
    :param real_part: Integer representing the real part of a complex number
    :param imaginary_part: Integer representing the imaginary part of a complex number
    :return: A string representing the complex number
    """
    if real_part == 0 and imaginary_part == 0:
        complex_number_string = 0
    elif real_part == 0:
        complex_number_string = str(imaginary_part) + 'i'
    elif imaginary_part == 0:
        complex_number_string = str(real_part)
    else:
        if imaginary_part > 0:
            complex_number_string = str(real_part) + "+" + str(imaginary_part) + 'i'
        else:
            complex_number_string = str(real_part) + str(imaginary_part) + 'i'
    return complex_number_string


def calculate_modulus(real_part: int, imaginary_part: int) -> float:
    """
    Computes the modulus of a complex number
    :param real_part:  Integer representing the real part of a complex number
    :param imaginary_part: Integer representing the imaginary part of a complex number
    :return: The modulus of the complex number
    """
    return (real_part ** 2 + imaginary_part ** 2) ** 0.5


def create_complex_number(real_part: int, imaginary_part: int) -> dict:
    """
    Creates a complex number in the form of a dictionary
    :param real_part: Integer representing the real part of a complex number
    :param imaginary_part: Integer representing the imaginary part of a complex number
    :return: A dictionary containing the real part and imaginary part of a complex number
    """
    return {"real_part": real_part, "imaginary_part": imaginary_part}


def get_real(complex_number: dict) -> int:
    """
    Provides the real part of a complex number
    :param complex_number: A dictionary containing the real and imaginary part of a complex number
    :return: The real part of the complex number
    """
    return complex_number["real_part"]


def get_imaginary(complex_number: dict) -> int:
    """
    Provides the imaginary part of a complex number
    :param complex_number: A dictionary containing the real and imaginary part of a complex number
    :return: The imaginary part of the complex number
    """
    return complex_number["imaginary_part"]


def add_a_number(number_list: list, parameters: str) -> list:
    """
    Adds a complex number to the current list of complex numbers
    :param number_list: Current list of complex numbers
    :param parameters: Complex number in the form of a string
    :return: The new list with the new complex number added
    """
    check_length = len(parameters.split())
    if check_length != 1:
        raise ValueError("Invalid parameters")
    number_list.append(extract_a_b_from_string(parameters))
    return number_list


def insert_number_at_position(number_list: list, parameters: str) -> list:
    """
    Inserts complex number at given position
    :param number_list: Current list of complex numbers
    :param parameters: Position to insert to and complex number in form of string
    :return: The new list with the new complex number inserted
    """
    check_length = len(parameters.split())
    if check_length != 3:
        raise ValueError("Invalid parameters")
    parameters = parameters.split(" at ")
    if int(parameters[1]) < 0 or int(parameters[1]) > len(number_list):
        raise ValueError("Parameters out of bounds")
    number_list.insert(int(parameters[1]), extract_a_b_from_string(parameters[0]))
    return number_list


def remove(number_list: list, parameters: str) -> list:
    """
    Removes a number from the current number list
    :param number_list: Current list of complex numbers
    :param parameters: Position/Positions from which to remove a number
    :return: The updated list
    """
    check_length = len(parameters.split())
    if parameters.isnumeric():
        if check_length != 1:
            raise ValueError("Invalid parameters")
        number_list.pop(int(parameters))
    elif " to " in parameters:
        if check_length != 3:
            raise ValueError("Invalid parameters")
        parameters = parameters.split(" to ")
        index_start = int(parameters[0])
        index_finish = int(parameters[1])
        if index_start < 0 or index_finish > len(number_list):
            raise ValueError("Parameters out of bounds")
        while index_finish >= index_start:
            number_list.pop(index_finish)
            index_finish -= 1
    return number_list


def replace_old_number_with_new_number(number_list: list, parameters: str) -> list:
    """
    Replaces a given number with a new one
    :param number_list: Current list of complex numbers
    :param parameters: Old number and new number to replace old number
    :return: The updated list
    """
    check_length = len(parameters.split())
    if check_length != 3:
        raise ValueError("Invalid input")
    parameters = parameters.split(" with ")
    for index in range(len(number_list)):
        if number_list[index] == extract_a_b_from_string(parameters[0]):
            number_list[index] = extract_a_b_from_string(parameters[1])
    return number_list


def list_display(number_list: list, parameters: str) -> list:
    """
    Displays the list of complex numbers
    :param number_list: Current list of complex numbers
    :param parameters: If empty, prints the whole list.
                        If contains real, prints only numbers with imaginary part = 0
                        If contains modulo, prints only numbers with modulus [ < | = | > ] than given modulus
    :return: The list to be printed
    """
    if not parameters:
        return number_list
    elif "real " in parameters.lower() and " to " in parameters.lower():
        check_length = len(parameters.split())
        if check_length != 4:
            raise ValueError("Invalid parameters")
        redundant, parameters = parameters.split(" ", 1)
        start, finish = parameters.split(" to ")
        if int(start) < 0 or int(finish) >= len(number_list):
            raise ValueError("Parameters out of bounds")
        to_print_list = []
        for i in range(int(start), int(finish) + 1):
            if get_imaginary(number_list[i]) == 0:
                to_print_list.append((number_list[i]))
        return to_print_list
    elif "modulo " in parameters.lower():
        check_length = len(parameters.split())
        if check_length != 3:
            raise ValueError("Invalid parameters")
        if " < " in parameters.lower():
            parameters = parameters.split(" < ")
            to_print_list = []
            for complex_number in number_list:
                modulus = calculate_modulus(get_real(complex_number), get_imaginary(complex_number))
                if modulus < int(parameters[1]):
                    to_print_list.append(complex_number)
            return to_print_list
        elif " = " in parameters.lower():
            parameters = parameters.split(" = ")
            to_print_list = []
            for complex_number in number_list:
                modulus = calculate_modulus(get_real(complex_number), get_imaginary(complex_number))
                if modulus == int(parameters[1]):
                    to_print_list.append(complex_number)
            return to_print_list
        elif " > " in parameters.lower():
            parameters = parameters.split(" > ")
            to_print_list = []
            for complex_number in number_list:
                modulus = calculate_modulus(get_real(complex_number), get_imaginary(complex_number))
                if modulus > int(parameters[1]):
                    to_print_list.append(complex_number)
            return to_print_list
        else:
            raise ValueError("Invalid parameters")
    else:
        raise ValueError("Invalid parameters")


def filter_list(number_list: list, parameters: str) -> list:
    """
    Filters the list and keeps only numbers based on a condition
    :param number_list: Current list of complex numbers
    :param parameters: If parameters is 'real', keeps only numbers having imaginary part =0
                        If parameters contains modulo, keeps only numbers with modulus [ < | = | > ] than given modulus
    :return: The updated list
    """
    check_length = len(parameters.split())
    if parameters == "real":
        new_list = []
        for complex_number in number_list:
            if get_imaginary(complex_number) == 0:
                new_list.append(complex_number)
        return new_list
    elif "modulo " in parameters.lower():
        if check_length != 3:
            raise ValueError("Invalid parameters")
        if " < " in parameters.lower():
            parameters = parameters.split(" < ")
            new_list = []
            for complex_number in number_list:
                modulus = calculate_modulus(get_real(complex_number), get_imaginary(complex_number))
                if modulus < int(parameters[1]):
                    new_list.append(complex_number)
            return new_list
        if " = " in parameters.lower():
            parameters = parameters.split(" = ")
            new_list = []
            for complex_number in number_list:
                modulus = calculate_modulus(get_real(complex_number), get_imaginary(complex_number))
                if modulus == int(parameters[1]):
                    new_list.append(complex_number)
            return new_list
        if " > " in parameters.lower():
            parameters = parameters.split(" > ")
            new_list = []
            for complex_number in number_list:
                modulus = calculate_modulus(get_real(complex_number), get_imaginary(complex_number))
                if modulus > int(parameters[1]):
                    new_list.append(complex_number)
            return new_list
        else:
            raise ValueError("Invalid parameters")
    else:
        raise ValueError("Invalid parameters")


def undo(stack: list) -> tuple:
    """
    Undoes the last operation
    :param stack: Contains all versions of the list of complex numbers
    :return: The stack after deleting the last operation, the number list containing the last operation after deletion
    """
    if len(stack) > 1:
        stack.pop()
        number_list = stack[len(stack) - 1][:]
        return stack, number_list
    else:
        stack = []
        number_list = []
        print("List is now empty")
    return stack, number_list


# return {"real_part": real_part, "imaginary_part": imaginary_part}
def test_function():
    test_list = [{"real_part": -4, "imaginary_part": 5}, {"real_part": 1, "imaginary_part": -9}]
    assert add_a_number(test_list, "4+4i") == [{"real_part": -4, "imaginary_part": 5},
                                               {"real_part": 1, "imaginary_part": -9},
                                               {"real_part": 4, "imaginary_part": 4}]
    assert insert_number_at_position(test_list, '2+3i at 1') == [{"real_part": -4, "imaginary_part": 5},
                                                                 {"real_part": 2, "imaginary_part": 3},
                                                                 {"real_part": 1, "imaginary_part": -9},
                                                                 {"real_part": 4, "imaginary_part": 4}]
    assert remove(test_list, '2') == [{"real_part": -4, "imaginary_part": 5},
                                      {"real_part": 2, "imaginary_part": 3},
                                      {"real_part": 4, "imaginary_part": 4}]
    test_list = [{"real_part": -4, "imaginary_part": 5},
                 {"real_part": 2, "imaginary_part": 3},
                 {"real_part": 1, "imaginary_part": -9},
                 {"real_part": 4, "imaginary_part": 4}]
    assert remove(test_list, '1 to 2') == [{"real_part": -4, "imaginary_part": 5},
                                           {"real_part": 4, "imaginary_part": 4}]
    test_list = [{"real_part": -4, "imaginary_part": 5},
                 {"real_part": 2, "imaginary_part": 3},
                 {"real_part": 1, "imaginary_part": -9},
                 {"real_part": 4, "imaginary_part": 4}]
    assert replace_old_number_with_new_number(test_list, '2+3i with 5') == [{"real_part": -4, "imaginary_part": 5},
                                                                            {"real_part": 5, "imaginary_part": 0},
                                                                            {"real_part": 1, "imaginary_part": -9},
                                                                            {"real_part": 4, "imaginary_part": 4}]
    assert extract_a_b_from_string('2+7i') == {'real_part': 2, 'imaginary_part': 7}
    assert extract_a_b_from_string('2-7i') == {'real_part': 2, 'imaginary_part': -7}
    assert extract_a_b_from_string('-2+7i') == {'real_part': -2, 'imaginary_part': 7}
    assert extract_a_b_from_string('-2-7i') == {'real_part': -2, 'imaginary_part': -7}
    assert extract_a_b_from_string('2') == {'real_part': 2, 'imaginary_part': 0}
    assert extract_a_b_from_string('-2') == {'real_part': -2, 'imaginary_part': 0}
    assert extract_a_b_from_string('7i') == {'real_part': 0, 'imaginary_part': 7}
    assert extract_a_b_from_string('-7i') == {'real_part': 0, 'imaginary_part': -7}
