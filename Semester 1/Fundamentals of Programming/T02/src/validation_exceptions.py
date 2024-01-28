class ValidationExceptions(Exception):
    def __init__(self, error_msgs):
        self._error_msgs = error_msgs

    @property
    def error_msgs(self):
        return self._error_msgs

    def __str__(self):
        return "Validation error: " + "\n".join(self.error_msgs)


class Validator(ValidationExceptions):
    def __init__(self, error_msgs):
        ValidationExceptions.__init__(self, error_msgs)
