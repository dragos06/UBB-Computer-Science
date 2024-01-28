class RepositoryExceptions(Exception):
    def __init__(self, error_msg):
        self._message = error_msg

    @property
    def message(self):
        return self._message

    def __str__(self):
        return "Repo error: " + str(self.message)


class IDAlreadyExistsError(RepositoryExceptions):
    def __init__(self):
        RepositoryExceptions.__init__(self, "ID already exists")
