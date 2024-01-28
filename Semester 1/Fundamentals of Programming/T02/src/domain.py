class Student:
    def __init__(self, student_id, name, attendance, grade):
        self.__student_id = student_id
        self.__name = name
        self.__attendance = attendance
        self.__grade = grade

    def __str__(self):
        return f"{self.__student_id}, {self.__name}, {self.__attendance}, {self.__grade}"

    @property
    def student_id(self):
        return self.__student_id

    @property
    def name(self):
        return self.__name

    @property
    def attendance(self):
        return self.__attendance

    @property
    def grade(self):
        return self.__grade

    @grade.setter
    def grade(self, value):
        self.__grade = value
