class RepositoryException(Exception):
    def __init__(self, error_message):
        self.__error_message = error_message

    @property
    def error_message(self):
        return self.__error_message

    def __str__(self):
        return "Repository error occurred: " + str(self.error_message)


class IDAlreadyExistsError(RepositoryException):
    def __init__(self):
        RepositoryException.__init__(self, "Question ID already exists")
