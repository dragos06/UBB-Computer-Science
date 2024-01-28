import unittest
from repository import MasterQuizFileRepository, QuizMemoryRepository, QuizFileRepository
from service import QuestionService


class Testing(unittest.TestCase):
    def setUp(self):
        self.__master_quiz_file_repository = MasterQuizFileRepository("test_master_quiz.txt")
        self.__quiz_file_repository = QuizFileRepository()
        self.__quiz_memory_repository = QuizMemoryRepository()
        self.__service = QuestionService(self.__quiz_memory_repository, self.__quiz_file_repository,
                                         self.__master_quiz_file_repository)

    def test_functionality_3_easy(self):
        self.__service.create_quiz('easy', '5', 'test_easy_quiz.txt')
        questions = self.__quiz_file_repository.load_from_file('test_easy_quiz.txt')
        nr_easy_questions = 0
        for question in questions.values():
            if question.difficulty == 'easy':
                nr_easy_questions += 1
        self.assertGreaterEqual(nr_easy_questions, 5 // 2)

    def test_functionality_3_medium(self):
        self.__service.create_quiz('medium', '6', 'test_medium_quiz.txt')
        questions = self.__quiz_file_repository.load_from_file('test_medium_quiz.txt')
        nr_medium_questions = 0
        for question in questions.values():
            if question.difficulty == 'medium':
                nr_medium_questions += 1
        self.assertGreaterEqual(nr_medium_questions, 6 // 2)

    def test_functionality_3_hard(self):
        self.__service.create_quiz('hard', '8', 'test_hard_quiz.txt')
        questions = self.__quiz_file_repository.load_from_file('test_hard_quiz.txt')
        nr_hard_questions = 0
        for question in questions.values():
            if question.difficulty == 'hard':
                nr_hard_questions += 1
        self.assertGreaterEqual(nr_hard_questions, 8 // 2)
