from src.validation_exceptions import Validator
from src.validation_exceptions import ValidationExceptions


class StudentValidator:
    def __init__(self):
        pass

    def validate(self, student):
        _errors = []
        name = student.name
        name = name.split(" ")
        if len(name) < 2:
            _errors.append("Name too short, it should have at least 2 words")
        for surname in name:
            if len(surname) < 3:
                _errors.append("Name too short, word should have at least 3 letters")
        if not str(student.attendance).isnumeric():
            _errors.append("Invalid attendance, it should be numeric")
        if int(student.attendance) < 0:
            _errors.append("Invalid attendance, it should be a positive integer")
        if not str(student.grade).isnumeric():
            _errors.append("Invalid grade, it should be numeric")
        if not (0 <= int(student.grade) <= 10):
            _errors.append("Invalid grade, it should be between 0 and 10")
        if len(_errors) > 0:
            raise ValidationExceptions(_errors)
