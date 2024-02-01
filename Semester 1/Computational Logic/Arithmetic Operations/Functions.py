def check_if_operation_is_valid(number: str, base: int) -> None:
    """
    Checks if the input number is valid for the given base
    :param number: A string representing a number in a specified base
    :param base: An integer specifying the base of the number
    :return: None
    Raises a ValueError if the number contains invalid characters or doesn't match the provided base
    """
    all_possible_characters = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F']
    for character in number:
        if character not in all_possible_characters:
            raise ValueError("Invalid numbers")
    if 'A' in number or 'B' in number or 'C' in number or 'D' in number or 'E' in number or 'F' in number:
        if base != 16:
            raise ValueError("Invalid base")
    elif max(int(digit) for digit in str(number)) >= base:
        raise ValueError("Invalid base")


def convert_hex_to_decimal(hex_str: str) -> int:
    """
    Converts a single hexadecimal digit to its decimal equivalent
    :param hex_str: A string representing a single hexadecimal digit ('A', 'B', 'C', 'D', 'E', 'F')
    :return: Returns the decimal equivalent of the hexadecimal digit
    """
    dec_dict = {'A': 10, 'B': 11, 'C': 12, 'D': 13, 'E': 14, 'F': 15}
    return dec_dict[hex_str]


def convert_str_to_int(character: str) -> int:
    """
    Converts a character (either a digit or a hexadecimal digit) to its integer representation
    :param character: A string representing a single digit in any base
    :return: Returns the integer representation of the input character
    """
    digit = character
    if digit.isnumeric():
        digit = int(digit)
    else:
        digit = convert_hex_to_decimal(digit)
    return digit


########################################################################################################################
def addition_in_base_h(a: str, b: str, base: int) -> str:
    """
    Performs addition of two numbers in the given base and returns the result
    :param a: A string representing the first number in a specified base
    :param b: A string representing the second number in a specified base
    :param base: An integer specifying the base of the numbers
    :return: Returns the sum of a and b in the specified base as a string
    """
    check_if_operation_is_valid(a, base)
    check_if_operation_is_valid(b, base)
    conversion_table = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'A', 'B', 'C', 'D', 'E', 'F']
    final_addition = ''
    carry = 0
    while a or b:
        if a:
            last_digit_a = convert_str_to_int(a[len(a) - 1])
        else:
            last_digit_a = 0
        if b:
            last_digit_b = convert_str_to_int(b[len(b) - 1])
        else:
            last_digit_b = 0
        addition = last_digit_a + last_digit_b + carry
        carry = conversion_table[addition // base]
        last_digit_addition = conversion_table[addition % base]
        final_addition = str(last_digit_addition) + final_addition
        a = a[:-1]
        b = b[:-1]
    if carry:
        final_addition = str(carry) + final_addition
    while final_addition[0] == '0' and len(final_addition) > 1:
        final_addition = final_addition[1:]
    return final_addition


########################################################################################################################
def multiplication_in_base_h(a: str, b: str, base: int) -> str:
    """
    Performs multiplication of a number by a single-digit number in the given base and returns the result
    :param a: A string representing the first number in a specified base
    :param b: A string representing a single-digit number in a specified base
    :param base: An integer specifying the base of the numbers
    :return: Returns the product of a and b in the specified base as a string
    """
    check_if_operation_is_valid(a, base)
    check_if_operation_is_valid(b, base)
    conversion_table = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'A', 'B', 'C', 'D', 'E', 'F']
    final_multiplication = ''
    carry = 0
    if len(a) < len(b):
        a, b = b, a
    if len(b) != 1:
        raise ValueError("Invalid numbers")
    b = convert_str_to_int(b)
    while a:
        last_digit_a = convert_str_to_int(a[len(a) - 1])
        multiplication = last_digit_a * b + convert_str_to_int(str(carry))
        carry = conversion_table[multiplication // base]
        last_digit_multiplication = conversion_table[multiplication % base]
        final_multiplication = str(last_digit_multiplication) + final_multiplication
        a = a[:-1]
    if carry:
        final_multiplication = str(carry) + final_multiplication
    while final_multiplication[0] == '0' and len(final_multiplication) > 1:
        final_multiplication = final_multiplication[1:]
    return final_multiplication


########################################################################################################################
def subtraction_in_base_h(a: str, b: str, base: int) -> str:
    """
    Performs subtraction of two numbers in the given base and returns the result
    :param a: A string representing the first number in a specified base
    :param b: A string representing the second number in a specified base
    :param base: An integer specifying the base of the numbers
    :return: Returns the difference of a minus b in the specified base as a string
    """
    check_if_operation_is_valid(a, base)
    check_if_operation_is_valid(b, base)
    conversion_table = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'A', 'B', 'C', 'D', 'E', 'F']
    final_subtraction = ''
    borrow = 0
    if len(a) < len(b):
        a, b = b, a
    while a or b:
        last_digit_a = convert_str_to_int(a[len(a) - 1])
        if b:
            last_digit_b = convert_str_to_int(b[len(b) - 1])
        else:
            last_digit_b = 0
        subtraction = last_digit_a - last_digit_b + borrow
        if subtraction < 0:
            last_digit_subtraction = conversion_table[base + subtraction]
            borrow = -1
        else:
            last_digit_subtraction = conversion_table[subtraction]
            borrow = 0
        final_subtraction = str(last_digit_subtraction) + final_subtraction
        a = a[:-1]
        b = b[:-1]
    while final_subtraction[0] == '0' and len(final_subtraction) > 1:
        final_subtraction = final_subtraction[1:]
    return final_subtraction


########################################################################################################################
def division_in_base_h(a: str, b: str, base: int):
    """
    Performs division of two numbers in the given base and returns the quotient and remainder
    :param a: A string representing the first number in a specified base
    :param b: A string representing a single-digit number in a specified base (non-zero)
    :param base: An integer specifying the base of the numbers
    :return: Returns a tuple containing the quotient and remainder of a divided by b in the specified base
    """
    check_if_operation_is_valid(a, base)
    check_if_operation_is_valid(b, base)
    conversion_table = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'A', 'B', 'C', 'D', 'E', 'F']
    final_quotient = ''
    if len(a) < len(b):
        a, b = b, a
    if len(b) != 1 or b == '0':
        raise ValueError("Invalid numbers")
    remainder = convert_str_to_int(a[0])
    b = convert_str_to_int(b)
    while a:
        quotient = conversion_table[remainder // b]
        remainder = conversion_table[remainder % b]
        final_quotient += str(quotient)
        a = a[1:]
        if not a:
            break
        remainder = convert_str_to_int(str(remainder)) * base + convert_str_to_int(a[0])
    while final_quotient[0] == '0' and len(final_quotient) > 1:
        final_quotient = final_quotient[1:]
    return final_quotient, remainder
