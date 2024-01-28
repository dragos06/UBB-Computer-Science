from src.repository_exceptions import RepositoryExceptions
from src.validation_exceptions import ValidationExceptions


class UI:
    def __init__(self, service):
        self.__service = service

    @staticmethod
    def print_menu():
        print("1. Add a new student: ")
        print("2. Display all students in order of their grades")
        print("3. Give bonuses, all students having P attendances will receive the bonus B")
        print("4. Display all students whose name include a given string, ordered by name")
        print("5. Exit")

    def add_student_ui(self):
        """
        Adds a student to the repository
        :return:
        """
        try:
            student_id = input("Please enter the student's id: ")
            name = input("Please enter the student's name: ")
            attendance = input("Please enter the student's attendance count:")
            grade = input("Please enter the student's grade: ")
            self.__service.add_student(student_id, name, attendance, grade)
        except RepositoryExceptions as re:
            print(re)
        except ValidationExceptions as ve:
            print(ve)
        except Exception as e:
            print(e)

    def display_students_by_grade_ui(self):
        to_print_list = self.__service.display_students_by_grade()
        for student in to_print_list:
            print(student)

    def give_bonuses_ui(self):
        p = input("Please enter the number of attendances P: ")
        b = input("Please enter the bonus B: ")
        try:
            p = int(p)
            b = int(b)
            self.__service.give_bonuses(p, b)
        except ValueError as ve:
            print("Error occurred" + str(ve))

    def display_students_by_given_string_ui(self):
        given_string = input("Please enter the given string: ")
        to_print_list = self.__service.display_students_by_given_string(given_string)
        for student in to_print_list:
            print(student)

    def start(self):
        while True:
            self.print_menu()
            print()
            user_option = input("Please choose an option: ")
            if user_option == '1':
                self.add_student_ui()
            elif user_option == '2':
                self.display_students_by_grade_ui()
            elif user_option == '3':
                self.give_bonuses_ui()
            elif user_option == '4':
                self.display_students_by_given_string_ui()
            elif user_option == '5':
                print("Exiting...")
                break
            else:
                print("Invalid input")
