#
# This is the program's UI module. The user interface and all interaction with the user (print and input statements) are
# found here
#
import functions


def print_menu():
    print("\n")
    print("(A) Add a number")
    print("add <number>\n"
          "insert <number> at <position>\n")
    print("(B) Modify numbers")
    print("remove <position>\n"
          "remove <start position> to <end position>\n"
          "replace <old number> with <new number>\n")
    print("(C) Display numbers having different properties")
    print("list\n"
          "list real <start position> to <end position>\n"
          "list modulo [ < | = | > ] <number>\n")
    print("(D) Filter the list")
    print("filter real\n"
          "filter modulo [ < | = | > ] <number>\n")
    print("(E) Undo")
    print(
        "undo – the last operation that modified program data is reversed. The user can undo all operations performed"
        "since program start by repeatedly calling this function.\n")
    print("(F) Exit")
    print("exit - exits the program\n")


def print_list(number_list):
    for complex_number in number_list:
        real_part = functions.get_real(complex_number)
        imaginary_part = functions.get_imaginary(complex_number)
        print(functions.set_complex_number(real_part, imaginary_part))


def user_input():
    number_list = functions.start_up()
    stack = [number_list[:]]
    while True:
        try:
            user_command = input("Please enter your command: ")
            if " " in user_command.strip():
                command, parameters = user_command.split(" ", 1)
            else:
                command = user_command
                parameters = None
            if command.strip().lower() == "add" and parameters:
                number_list = functions.add_a_number(number_list, parameters)
                stack.append(number_list[:])
            elif command.strip().lower() == "insert" and parameters:
                number_list = functions.insert_number_at_position(number_list, parameters)
                stack.append(number_list[:])
            elif command.strip().lower() == "remove" and parameters:
                number_list = functions.remove(number_list, parameters)
                stack.append(number_list[:])
            elif command.strip().lower() == "replace" and parameters:
                number_list = functions.replace_old_number_with_new_number(number_list, parameters)
                stack.append(number_list[:])
            elif command.strip().lower() == "list":
                to_print_list = functions.list_display(number_list, parameters)
                if to_print_list:
                    print_list(to_print_list)
                else:
                    print("No elements found")
            elif command.strip().lower() == "filter" and parameters:
                new_list = functions.filter_list(number_list, parameters)
                if new_list:
                    number_list = new_list
                    stack.append(number_list[:])
                else:
                    print("No elements left")
                    number_list = []
                    stack.append(number_list[:])
            elif command.strip().lower() == "undo" and not parameters:
                stack, number_list = functions.undo(stack)
            elif command.strip().lower() == "exit" and not parameters:
                print("Exiting...")
                break
            else:
                raise ValueError("Invalid command")
        except ValueError as validation_error:
            print("Error occurred: ", validation_error)
