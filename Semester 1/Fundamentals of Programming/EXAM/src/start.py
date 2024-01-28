from domain import Question
from repository import QuizFileRepository, QuizMemoryRepository, MasterQuizFileRepository
from service import QuestionService
from ui import UI

master_quiz_file_repository = MasterQuizFileRepository("master_quiz.txt")
memory_repository = QuizMemoryRepository()
file_repository = QuizFileRepository()
service = QuestionService(memory_repository, file_repository, master_quiz_file_repository)
ui = UI(service)

ui.start()
