class RepoExceptions(Exception):
    def __init__(self, error_message):
        self.__error_message = error_message

    @property
    def error_message(self):
        return self.__error_message

    def __str__(self):
        return "Repository error: " + str(self.error_message)


class OutOfBoundsError(RepoExceptions):
    def __init__(self):
        RepoExceptions.__init__(self, "Place outside of bounds")


class PlaceAlreadyUsedError(RepoExceptions):
    def __init__(self):
        RepoExceptions.__init__(self, "Place already used")


class InvalidInputError(RepoExceptions):
    def __init__(self):
        RepoExceptions.__init__(self, "Invalid inputs, coordinates should be positive numbers")
