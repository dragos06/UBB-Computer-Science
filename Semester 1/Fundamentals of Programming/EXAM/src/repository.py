import os.path
from domain import Question
from repository_exception import IDAlreadyExistsError


class QuizMemoryRepository:
    def __init__(self):
        self.__questions = {}

    def add(self, question):
        """
        Adds question to repository
        :param question: Question object
        """
        if question.question_id in self.__questions:
            raise IDAlreadyExistsError
        self.__questions[question.question_id] = question

    def get_all(self):
        """
        :return: all questiosn from the repository
        """
        return list(self.__questions.values())

    @property
    def size(self):
        return len(self.get_all())


class MasterQuizFileRepository(QuizMemoryRepository):
    def __init__(self, file_name):
        super().__init__()
        self.__file_name = file_name
        self.load_from_file()

    def add(self, question):
        """
        Adds question to memory repository as well as file
        :param question: Question object
        """
        super().add(question)
        self.save_to_file()

    def load_from_file(self):
        """
        Loads from file all questions and adds to memory repository
        """
        try:
            if os.path.exists(self.__file_name):
                file = open(self.__file_name, 'r')
                lines = file.readlines()
                for line in lines:
                    question_id, question_text, choice_a, choice_b, choice_c, correct_choice, difficulty = line.strip().split(
                        ";")
                    question = Question(question_id, question_text, choice_a, choice_b, choice_c, correct_choice,
                                        difficulty)
                    super().add(question)
        except EOFError:
            raise FileNotFoundError("File not found")

    def save_to_file(self):
        """
        Saves all questions to file
        """
        file = open(self.__file_name, 'w')
        for question in self.get_all():
            file.write(
                f"{question.question_id};{question.question_text};{question.choice_a};{question.choice_b};{question.choice_c};{question.correct_choice};{question.difficulty}\n")


class QuizFileRepository:
    def __init__(self):
        pass

    def load_from_file(self, file_name):
        """
        Loads quiz from file
        :param file_name: name of file where quiz is stored
        :return: all questions from quiz
        """
        try:
            if os.path.exists(file_name):
                temp_data = {}
                file = open(file_name, 'r')
                lines = file.readlines()
                for line in lines:
                    question_id, question_text, choice_a, choice_b, choice_c, correct_choice, difficulty = line.strip().split(
                        ";")
                    question = Question(question_id, question_text, choice_a, choice_b, choice_c, correct_choice,
                                        difficulty)
                    temp_data[question.question_id] = question
                return temp_data
        except EOFError:
            raise FileNotFoundError("File not found")

    def save_to_file(self, questions: dict, file_name: str):
        """
        Saves the created quiz
        :param questions: The questions in the quiz
        :param file_name: the file name of the file which will be created
        """
        file = open(file_name, 'w')
        for question in questions.values():
            file.write(
                f"{question.question_id};{question.question_text};{question.choice_a};{question.choice_b};{question.choice_c};{question.correct_choice};{question.difficulty}\n")
