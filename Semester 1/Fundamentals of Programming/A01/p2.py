# Solve the problem from the second set here

# PROBLEM 6 START
def is_leap_year(n: int) -> bool:
    if n % 400 == 0:
        return True
    if n % 100 == 0:
        return False
    if n % 4 == 0:
        return True
    else:
        return False


days_of_months_nonleap = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
# days_of_months_leap = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
months = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November',
          'December']
print(
    "6. Determine a calendar date starting from two integer numbers representing the year and the day number inside"
    " that year. "
    "Take into account leap years.")
year = int(input("Please enter the year: "))
days = int(input("Please enter the number of days inside that year: "))
month_index = 0
if not is_leap_year(year):
    while days > 0:
        days -= days_of_months_nonleap[month_index]
        if days <= 0:
            break
        month_index += 1
    print('The calendar date is: ', year, ' ', months[month_index], ' ', days + days_of_months_nonleap[month_index])
else:
    days_of_months_nonleap[1] += 1
    while days > 0:
        days -= days_of_months_nonleap[month_index]
        if days <= 0:
            break
        month_index += 1
    print('The calendar date is: ', year, ' ', months[month_index], ' ', days + days_of_months_nonleap[month_index])


# PROBLEM 6 END

# PROBLEM 10 START
def palindrome(n: int) -> int:
    m = 0
    while n:
        m = m * 10 + n % 10
        n = int(n / 10)
    return m


print(
    "10. The palindrome of a number is the number obtained by reversing the order of its digits."
    "For a given natural number n, determine its palindrome.")
user_number = int(input("Please enter a natural number: "))
print(f"The palindrome of {user_number} is: ", palindrome(user_number))
# PROBLEM 10 END
