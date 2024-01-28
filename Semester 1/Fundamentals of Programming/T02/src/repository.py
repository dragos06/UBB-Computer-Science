import os.path
from src.domain import Student
from src.repository_exceptions import IDAlreadyExistsError


class StudentMemoryRepository:
    def __init__(self):
        self.__students = {}

    def store(self, student: Student):
        """
        Stores student to memory repository
        :param student: student object
        """
        if int(student.student_id) in self.__students:
            raise IDAlreadyExistsError
        self.__students[student.student_id] = student

    def get_all(self):
        return list(self.__students.values())

    def get_all_ids(self):
        return self.__students.keys()


class StudentFileRepository(StudentMemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.load_students_from_file()

    def store(self, student: Student):
        """
        stores students to file repository
        :param student:
        :return:
        """
        super().store(student)
        self.save_students_to_file()

    def load_students_from_file(self):
        try:
            if os.path.exists(self.__file_name):
                file = open(self.__file_name, 'r')
                lines = file.readlines()
                for line in lines:
                    student_id, name, attendance, grade = line.strip().split(', ')
                    student_id = student_id
                    attendance = attendance
                    grade = grade
                    student = Student(student_id, name, attendance, grade)
                    self.store(student)
        except EOFError:
            raise FileNotFoundError("File not found")

    def save_students_to_file(self):
        file = open(self.__file_name, 'w')
        for student in self.get_all():
            file.write(f"{student.student_id}, {student.name}, {student.attendance}, {student.grade}\n")
