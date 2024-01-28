class Question:
    def __init__(self, question_id, question_text, choice_a, choice_b, choice_c, correct_choice, difficulty):
        self.__question_id = question_id
        self.__question_text = question_text
        self.__choice_a = choice_a
        self.__choice_b = choice_b
        self.__choice_c = choice_c
        self.__correct_choice = correct_choice
        self.__difficulty = difficulty


    def __str__(self):
        return f"{self.question_text}: {self.choice_a}, {self.choice_b}, {self.choice_c}"

    @property
    def question_id(self):
        return self.__question_id

    @property
    def question_text(self):
        return self.__question_text

    @property
    def choice_a(self):
        return self.__choice_a

    @property
    def choice_b(self):
        return self.__choice_b

    @property
    def choice_c(self):
        return self.__choice_c

    @property
    def correct_choice(self):
        return self.__correct_choice

    @property
    def difficulty(self):
        return self.__difficulty
