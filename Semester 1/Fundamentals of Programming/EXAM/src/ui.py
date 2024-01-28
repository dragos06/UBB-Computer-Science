class UI:
    def __init__(self, service):
        self.__service = service

    def add_question_ui(self, parameters):
        try:
            parameters = parameters.split(';')
            if len(parameters) != 7:
                raise ValueError("Invalid input")
            question_id, question_text, choice_a, choice_b, choice_c, correct_choice, difficulty = parameters
            self.__service.add_question(question_id, question_text, choice_a, choice_b, choice_c, correct_choice,
                                        difficulty)
        except Exception as e:
            print(e)

    def create_quiz_ui(self, parameters):
        try:
            parameters = parameters.split()
            if len(parameters) != 3:
                raise ValueError("Invalid input")
            difficulty, number_of_questions, file_name = parameters
            self.__service.create_quiz(difficulty, number_of_questions, file_name)
        except Exception as e:
            print(e)

    def start_quiz_ui(self, parameters):
        try:
            parameters = parameters.split()
            if len(parameters) != 1:
                raise ValueError("Invalid input")
            file_name = parameters[0]
            score = self.__service.start_quiz(file_name)
            print(f"Your score is {score}")
        except Exception as e:
            print(e)

    def start(self):
        if self.__service.file_question_size() == 0:
            self.__service.random_question_generator()
        while True:
            user_option = input("Please choose an option: ")
            command = ''
            parameters = ''
            try:
                command, parameters = user_option.split(" ", maxsplit=1)
            except ValueError:
                pass
            if command.lower() == 'add':
                self.add_question_ui(parameters)
            elif command.lower() == "create":
                self.create_quiz_ui(parameters)
            elif command.lower() == "start":
                self.start_quiz_ui(parameters)
            else:
                print("Invalid input")
