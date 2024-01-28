#
# Write the implementation for A5 in this file
#
def create_complex_nr(complex_str):
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
    if imaginary_part == '-i':
        imaginary_part = '-1'
    elif imaginary_part == '+i' or imaginary_part == 'i':
        imaginary_part = '1'
    imaginary_part = imaginary_part.replace('i', '')
    if not imaginary_part:
        imaginary_part = 0
    if not real_part:
        real_part = 0
    return [float(real_part), float(imaginary_part)]
    # return {'real': float(real_part), 'imaginary': float(imaginary_part)}


def set_complex_nr(real_part_str, imaginary_part_str):
    complex_number_str = ''
    if real_part_str == '0' and imaginary_part_str == '0':
        return '0'
    elif imaginary_part_str == '1':
        imaginary_part_str = 'i'
    elif imaginary_part_str == '-1':
        imaginary_part_str = '-i'
    elif imaginary_part_str == '0':
        return real_part_str
    else:
        imaginary_part_str = imaginary_part_str + 'i'
    if real_part_str == '0':
        complex_number_str += imaginary_part_str
    else:
        if (len(imaginary_part_str) == 2 and imaginary_part_str[0] != '-') or len(imaginary_part_str) > 2:
            if float(imaginary_part_str[:-1]) < 0:
                complex_number_str = real_part_str + imaginary_part_str
            elif float(imaginary_part_str[:-1]) > 0:
                complex_number_str = real_part_str + '+' + imaginary_part_str
        elif imaginary_part_str == '-i':
            complex_number_str = real_part_str + imaginary_part_str
        elif imaginary_part_str == 'i':
            complex_number_str = real_part_str + '+' + imaginary_part_str
    return complex_number_str


def create_complex_list_and_dictionary(complex_str_list):
    complex_list = []
    for complex_str_number in complex_str_list:
        complex_list.append(create_complex_nr(complex_str_number))
    return complex_list


def calculate_modulus(complex_number):
    real_part = get_real(complex_number)
    imaginary_part = get_imaginary(complex_number)
    return (real_part ** 2 + imaginary_part ** 2) ** 0.5


#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def get_real(complex_nr):
    if isinstance(complex_nr, list):
        return complex_nr[0]
    elif isinstance(complex_nr, dict):
        return complex_nr['real']


def get_imaginary(complex_nr):
    if isinstance(complex_nr, list):
        return complex_nr[1]
    elif isinstance(complex_nr, dict):
        return complex_nr['imaginary']


def set_real(complex_number_float):
    if isinstance(complex_number_float, list):
        if complex_number_float[0].is_integer():
            real_number_str = str(int(complex_number_float[0]))
        else:
            real_number_str = str(complex_number_float[0])
        return real_number_str
    elif isinstance(complex_number_float, dict):
        if complex_number_float['real'].is_integer():
            real_number_str = str(int(complex_number_float['real']))
        else:
            real_number_str = str(complex_number_float['real'])
        return real_number_str


def set_imaginary(complex_number_float):
    if isinstance(complex_number_float, list):
        if complex_number_float[1].is_integer():
            real_number_str = str(int(complex_number_float[1]))
        else:
            real_number_str = str(complex_number_float[1])
        return real_number_str
    elif isinstance(complex_number_float, dict):
        if complex_number_float['imaginary'].is_integer():
            real_number_str = str(int(complex_number_float['imaginary']))
        else:
            real_number_str = str(complex_number_float['imaginary'])
        return real_number_str


def get_real_list(complex_nr: list):
    return complex_nr[0]


def set_real_list(complex_number_float):
    if complex_number_float[0].is_integer():
        real_number_str = str(int(complex_number_float[0]))
    else:
        real_number_str = str(complex_number_float[0])
    return real_number_str


def get_imaginary_list(complex_nr: list):
    return complex_nr[1]


def set_imaginary_list(complex_number_float):
    if complex_number_float[1].is_integer():
        imaginary_number_str = str(int(complex_number_float[1]))
    else:
        imaginary_number_str = str(complex_number_float[1])
    return imaginary_number_str


#
# Write below this comment 
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def get_real_dict(complex_nr):
    return complex_nr['real']


def set_real_dict(complex_number_float):
    if complex_number_float['real'].is_integer():
        real_number_str = str(int(complex_number_float['real']))
    else:
        real_number_str = str(complex_number_float['real'])
    return real_number_str


def get_imaginary_dict(complex_nr):
    return complex_nr['imaginary']


def set_imaginary_dict(complex_number_float):
    if complex_number_float['imaginary'].is_integer():
        imaginary_number_str = str(int(complex_number_float['imaginary']))
    else:
        imaginary_number_str = str(complex_number_float['imaginary'])
    return imaginary_number_str


#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def set_a(complex_str_list: list):
    """
    Length and elements of the longest subarray of numbers where each number's modulus is in the [0, 10] range.
    :param complex_str_list: A list containing every complex number in its string form
    :return: A tuple of the length of the maximum sequence and the elements of the maximum sequence
    """
    complex_list = create_complex_list_and_dictionary(complex_str_list)
    sequence = 0
    sequence_elements = []
    max_sequence = -1
    max_sequence_elements = []
    for complex_number in complex_list:
        modulus = calculate_modulus(complex_number)
        if 0 <= modulus <= 10:
            sequence += 1
            sequence_elements.append(complex_number)
        else:
            sequence = 0
            sequence_elements = []
        if sequence > max_sequence:
            max_sequence = sequence
            max_sequence_elements = sequence_elements[:]
    return max_sequence, max_sequence_elements


def set_b(complex_str_list: list):
    """
    The length and elements of the longest increasing subsequence, when considering each number's modulus
    :param complex_str_list: A list containing every complex number in its string form
    :return: A tuple containing the length of the maximum sequence and the elements of the maximum sequence
    """
    complex_list = create_complex_list_and_dictionary(complex_str_list)
    modulus_list = []
    for complex_number in complex_list:
        modulus_list.append(calculate_modulus(complex_number))
    modulus_list_length = len(modulus_list)
    lis_lengths = [1] * modulus_list_length
    prev_index = [-1] * modulus_list_length
    for i in range(1, modulus_list_length):
        for j in range(0, i):
            if modulus_list[i] > modulus_list[j] and lis_lengths[i] < lis_lengths[j] + 1:
                lis_lengths[i] = lis_lengths[j] + 1
                prev_index[i] = j
    max_length_index = lis_lengths.index(max(lis_lengths))
    solution = []
    while max_length_index != -1:
        solution.insert(0, complex_list[max_length_index])
        max_length_index = prev_index[max_length_index]
    return max(lis_lengths), solution


#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#
def print_menu():
    print("Complex Numbers Menu\n\n")
    print("1. Input list of complex numbers (in z = a + bi form)")
    print("2. Display the entire list of numbers")
    print(
        "3. Length and elements of a longest subarray of numbers where each number's modulus is in the [0, 10] range.")
    print("4. The length and elements of a longest increasing subsequence, when considering each number's modulus")
    print("5. Exit\n")


def print_solution_list(complex_number_list):
    for complex_numbers in complex_number_list:
        real_part = set_real(complex_numbers)
        imaginary_part = set_imaginary(complex_numbers)
        print(set_complex_nr(real_part, imaginary_part))


def print_solution_str(complex_str_list):
    i = 0
    for complex_number_str in complex_str_list:
        i += 1
        print(f"z{i}: {complex_number_str}")


def user_input():
    input_list = ['3-4i', '2+3i', '10+10i', '-1-2i', '-7+i', '3-4i', '-2+3i', '10-10i', '-1+2i', '7+i']
    while True:
        user_option = int(input("Please choose an option from the list above: "))
        if user_option == 1:
            input_list = input("Please enter a list of complex numbers separated by a comma:\n>>>").split(', ')
        if user_option == 2:
            print("The list of complex numbers is:")
            print_solution_str(input_list)
            print('\n')
        if user_option == 3:
            set_a_results = set_a(input_list)
            print(f"The length of the longest subarray is: {set_a_results[0]}")
            print("The longest subarray is:")
            print_solution_list(set_a_results[1])
            print('\n')
        if user_option == 4:
            set_b_results = set_b(input_list)
            print(f"The length of the longest increasing subsequence is: {set_b_results[0]}")
            print("The longest increasing subsequence is:")
            print_solution_list(set_b_results[1])
            print('\n')
        if user_option == 5:
            print("Exiting")
            break


if __name__ == "__main__":
    print_menu()
    user_input()
