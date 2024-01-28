from src.repository import StudentFileRepository
from src.services import StudentService
from src.validator import StudentValidator
from src.ui import UI

student_repository = StudentFileRepository("students.txt")
student_validator = StudentValidator()
student_service = StudentService(student_repository, student_validator)
ui = UI(student_service)

ui.start()
