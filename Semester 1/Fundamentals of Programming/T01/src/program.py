#
# Functions section
#
def create_phone(manufacturer: str, model: str, price: int) -> dict:
    return {"Manufacturer": manufacturer, "Model": model, "Price": price}


def get_manufacturer(phone: dict) -> str:
    """
    Provides the manufacturer of a phone
    :param phone: dictionary containing all phone specifications
    :return: the phone manufacturer
    """
    return phone["Manufacturer"]


def get_model(phone: dict) -> str:
    """
    Provides the model of a phone
    :param phone: dictionary containing all phone specifications
    :return: the phone model
    """
    return phone["Model"]


def get_price(phone: dict):
    return phone["Price"]


def print_manufacturer(phone_list: list, manufacturer: str) -> list:
    found = False
    to_print_list = []
    for i in range(len(phone_list)):
        if (manufacturer.strip()).lower() in (get_manufacturer(phone_list[i]).lower()):
            to_print_list.append(phone_list[i])
            found = True
    if found:
        return to_print_list
    else:
        raise ValueError("Phones not found")


def increase_price(phone_list: list, manufacturer: str, model: str, amount: int) -> list:
    """
    This function will increase the price of a given phone by a given amount
    :param phone_list: The list containing all phone dictionaries
    :param manufacturer: The desired manufacturer
    :param model: The desired model
    :param amount: The amount by which to increase the phone price
    :return: The updated list containing all phone dictionaries
    """
    found = False
    for i in range(len(phone_list)):
        if get_manufacturer(phone_list[i]).strip() == manufacturer.strip() and get_model(phone_list[i]) == model:
            phone_list[i]["Price"] += amount
            found = True
    if not found:
        raise ValueError("Phone not found")
    return phone_list


def increase_all_percent(phone_list: list, given_percent: int) -> list:
    for i in range(len(phone_list)):
        phone_list[i]["Price"] = phone_list[i]["Price"] + (given_percent / 100 * phone_list[i]["Price"])
    return phone_list


#
# User interface section
#
def option_one(phone_list: list) -> list:
    manufacturer = input("Please enter the manufacturer: ")
    model = input("Please enter the model: ")
    price = input("Please enter the price: ")
    if len(manufacturer) < 3 or len(model) < 3 or len(price) < 3:
        raise ValueError("Invalid input, strings too short")
    if not price.isdigit():
        raise ValueError("Invalid price")
    price = int(price)
    phone_list.append(create_phone(manufacturer, model, price))
    return phone_list


def option_two(phone_list: list):
    desired_manufacturer = input("Please enter the manufacturer: ")
    if not desired_manufacturer:
        raise ValueError("String is empty")
    to_print_list = print_manufacturer(phone_list, desired_manufacturer)
    for dictionary in to_print_list:
        print(
            f"Manufacturer: {get_manufacturer(dictionary)}\nModel: {get_model(dictionary)}\nPrice: {get_price(dictionary)}")
        print('\n')


def option_three(phone_list: list) -> list:
    manufacturer = input("Please specify the manufacturer: ")
    model = input("Please specify the model: ")
    amount = input("Please specify the amount to increase the price of the phone with: ")
    if not amount.isdigit():
        raise ValueError("Invalid amount")
    amount = int(amount)
    return increase_price(phone_list, manufacturer, model, amount)


def option_four(phone_list: list) -> list:
    percent = input("Please specify the percent to increase all phone prices by, between -50 and 100: ")
    if not percent.isdigit():
        raise ValueError("Invalid percent")
    percent = int(percent)
    if not -50 < percent < 100:
        raise ValueError("Percent out of bounds")
    return increase_all_percent(phone_list, percent)


def print_menu():
    print("1. Add a phone")
    print("2. Display all phones from a given manufacturer")
    print("3. Increase the price of a phone with a given amount")
    print("4. Increase the price of all phones with a given percent between -50 and 100")


def start():
    phone_list = []
    while True:
        try:
            option = input("Please choose an option from above: ")
            if option == '1':
                phone_list = option_one(phone_list)
            elif option == '2':
                option_two(phone_list)
            elif option == '3':
                phone_list = option_three(phone_list)
            elif option == '4':
                phone_list = option_four(phone_list)
            else:
                print("Invalid input for option")
        except ValueError as validation_error:
            print("Error occurred: %s" % validation_error)


print_menu()
start()
