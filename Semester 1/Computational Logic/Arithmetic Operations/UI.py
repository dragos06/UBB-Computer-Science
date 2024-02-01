import Functions


def print_menu():
    print("\n     Arithmetic Operations for Positive Integers\n")
    print("1. Addition")
    print("2. Subtraction")
    print("3. Multiplication by one digit")
    print("4. Division by one digit")
    print("5. Exit\n")


def option_one():
    number1 = input("Please enter the first term: ")
    number2 = input("Please enter the second term: ")
    base = input("Please enter the base: ")
    if not base.isnumeric() or base not in ['2', '3', '4', '5', '6', '7', '8', '9', '10', '16']:
        raise ValueError("Invalid base")
    base = int(base)
    result = Functions.addition_in_base_h(number1.upper(), number2.upper(), base)
    print(f"{number1}({base}) + {number2}({base}) = {result}({base})")


def option_two():
    number1 = input("Please enter the first term: ")
    number2 = input("Please enter the second term: ")
    base = input("Please enter the base: ")
    if not base.isnumeric() or base not in ['2', '3', '4', '5', '6', '7', '8', '9', '10', '16']:
        raise ValueError("Invalid base")
    base = int(base)
    result = Functions.subtraction_in_base_h(number1.upper(), number2.upper(), base)
    print(f"{number1}({base}) - {number2}({base}) = {result}({base})")


def option_three():
    number1 = input("Please enter the first term: ")
    number2 = input("Please enter the second term: ")
    base = input("Please enter the base: ")
    if not base.isnumeric() or base not in ['2', '3', '4', '5', '6', '7', '8', '9', '10', '16']:
        raise ValueError("Invalid base")
    base = int(base)
    result = Functions.multiplication_in_base_h(number1.upper(), number2.upper(), base)
    print(f"{number1}({base}) * {number2}({base}) = {result}({base})")


def option_four():
    number1 = input("Please enter the first term: ")
    number2 = input("Please enter the second term: ")
    base = input("Please enter the base: ")
    if not base.isnumeric() or base not in ['2', '3', '4', '5', '6', '7', '8', '9', '10', '16']:
        raise ValueError("Invalid base")
    base = int(base)
    result = Functions.division_in_base_h(number1.upper(), number2.upper(), base)
    print(f"{number1}({base}) + {number2}({base}) = {result[0]}({base}) remainder {result[1]}({base})")


def start():
    while True:
        try:
            user_option = input("Please choose an option: ")
            if user_option == '1':
                option_one()
            elif user_option == '2':
                option_two()
            elif user_option == '3':
                option_three()
            elif user_option == '4':
                option_four()
            elif user_option == '5':
                print("Exiting...")
                break
            else:
                raise ValueError("Invalid input")
        except ValueError as value_error:
            print("Error occurred: ", value_error)
