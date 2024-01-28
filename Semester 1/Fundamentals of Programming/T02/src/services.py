from src.validator import StudentValidator
from src.domain import Student


class StudentService:
    def __init__(self, repository, student_validator):
        self.__repository = repository
        self.__student_validator = student_validator

    def add_student(self, student_id: int, name: str, attendance: int, grade: int):
        """
        Adds a student to the repository
        :param student_id:  Student's ID
        :param name: Student's name
        :param attendance: Student's attendance count
        :param grade: Student's grade
        """
        student = Student(student_id, name, attendance, grade)
        self.__student_validator.validate(student)
        self.__repository.store(student)

    def give_bonuses(self, p, b):
        students = self.__repository.get_all()
        for student in students:
            if student.attendance >= p:
                if student.grade + b <= 10:
                    student.grade += b
                elif student.grade + b > 10:
                    student.grade = 10

    def display_students_by_grade(self):
        students = self.__repository.get_all()
        for i in range(len(students) - 1):
            for j in range(i + 1, len(students)):
                if students[i].grade < students[j].grade:
                    students[i], students[j] = students[j], students[i]
        for i in range(len(students) - 1):
            for j in range(i + 1, len(students)):
                if students[i].grade == students[j].grade:
                    if students[i].name > students[j].name:
                        students[i], students[j] = students[j], students[i]
        return students

    def display_students_by_given_string(self, given_string):
        students = self.__repository.get_all()
        given_students = []
        for student in students:
            if given_string.lower() in student.name.lower():
                given_students.append(student)
        for i in range(len(given_students) - 1):
            for j in range(i + 1, len(given_students)):
                if given_students[i].name > given_students[j].name:
                    given_students[i], given_students[j] = given_students[j], given_students[i]
        return given_students
