from domain import Question


class QuestionService:
    def __init__(self, memory_repository, file_repository, master_file_repository):
        self.__memory_repository = memory_repository
        self.__file_repository = file_repository
        self.__master_file_repository = master_file_repository

    def add_question(self, question_id, question_text, choice_a, choice_b, choice_c, correct_choice, difficulty):
        """
        Adds question to repository
        :param question_id: id of question
        :param question_text: text of question
        :param choice_a: first choice
        :param choice_b: second choice
        :param choice_c: third choice
        :param correct_choice: correct choice
        :param difficulty: difficulty
        :raises: ValueError: if difficulty is not selectable or correct choice not in all choices
        """
        question = Question(question_id, question_text, choice_a, choice_b, choice_c, correct_choice, difficulty)
        if difficulty not in ['easy', 'medium', 'hard']:
            raise ValueError("Incorrect difficulty")
        if correct_choice not in [choice_a, choice_b, choice_c]:
            raise ValueError("Incorrect correct choice")
        self.__master_file_repository.add(question)

    def create_quiz(self, difficulty: str, number_of_questions: str, file_name: str):
        """
        Creates a quiz based on parameters
        :param difficulty: difficulty of quiz
        :param number_of_questions: how many questions to be in the quiz
        :param file_name: name of file where to store
        :raises: ValueError if there are not enough questions
        """
        if difficulty not in ['easy', 'medium', 'hard']:
            raise ValueError("Incorrect difficulty")
        questions_to_create_quiz = {}
        number_of_questions = int(number_of_questions)
        for question in self.__master_file_repository.get_all():
            if question.difficulty == difficulty:
                questions_to_create_quiz[question.question_id] = question
            if len(questions_to_create_quiz) == number_of_questions:
                break
        if len(questions_to_create_quiz) < number_of_questions / 2:
            raise ValueError(f"Not enough {difficulty} questions")
        if len(questions_to_create_quiz) < number_of_questions:
            for question in self.__master_file_repository.get_all():
                if question.difficulty != difficulty:
                    questions_to_create_quiz[question.question_id] = question
                if len(questions_to_create_quiz) == number_of_questions:
                    break
        if len(questions_to_create_quiz) < number_of_questions:
            raise ValueError("Not enough questions")
        self.__file_repository.save_to_file(questions_to_create_quiz, file_name)

    def sort_questions_by_difficulty(self, questions):
        """
        Sorts all questions by difficulty, easy -> medium -> hard
        :param questions: questions list
        :return: sorted questions
        """
        for i in range(len(questions) - 1):
            for j in range(i + 1, len(questions)):
                if questions[i].difficulty == 'medium' and questions[j].difficulty == 'easy':
                    questions[i], questions[j] = questions[j], questions[i]
                elif questions[i].difficulty == 'hard' and questions[j].difficulty == 'easy':
                    questions[i], questions[j] = questions[j], questions[i]
                elif questions[i].difficulty == 'hard' and questions[j].difficulty == 'medium':
                    questions[i], questions[j] = questions[j], questions[i]
        return questions

    def start_quiz(self, file_name):
        """
        Starts quiz
        :param file_name: name of file where quiz is stored
        :return: user score based on correct answers
        """
        user_score = 0
        quiz_questions_dict = self.__file_repository.load_from_file(file_name)
        quiz_questions = []
        for question in quiz_questions_dict.values():
            quiz_questions.append(question)
        quiz_questions = self.sort_questions_by_difficulty(quiz_questions)
        for question in quiz_questions:
            print(question)
            user_choice = input("Please choose an answer: ")
            if user_choice == question.correct_choice:
                if question.difficulty == 'easy':
                    user_score += 1
                elif question.difficulty == 'medium':
                    user_score += 2
                elif question.difficulty == 'hard':
                    user_score += 3
        return user_score

    def display(self):
        return self.__memory_repository.get_all()

    def random_question_generator(self):
        """
        Default questions to use in case master_quiz file does not exist
        """
        default_questions = [Question('1', 'Which number is the largest', '1', '4', '3', '4', 'easy'),
                             Question('2', 'Which number is the smallest', '-3', '3', '0', '-3', 'easy'),
                             Question('3', 'Which number is prime', '2', '32', '9', '2', 'easy'),
                             Question('4', 'Which country has the largest GPD', 'Brazil', 'China', 'UK', 'China',
                                      'medium'),
                             Question('5', 'Which is not a fish', 'carp', 'orca', 'eel', 'orca', 'medium'),
                             Question('6', 'Name of the first satellite', 'Apollo', 'Sputnik', 'Zaria', 'Sputnik',
                                      'medium'),
                             Question('7', 'Which Apollo mission did not make it to the moon', '11', '13', '17', '13',
                                      'hard'),
                             Question('8', 'A mole can be', 'animal', 'quantity', 'both', 'both', 'hard'),
                             Question('9', "Name El Cid's horse", 'Babieca', 'Abu', 'Santiago', 'Babieca', 'hard'),
                             Question('10', 'The Western Roman Empire fell in', '654', '546', '476', '476', 'hard')]
        for question in default_questions:
            self.__master_file_repository.add(question)

    def file_question_size(self):
        """
        :return: Size of master questions file
        """
        return self.__master_file_repository.size
