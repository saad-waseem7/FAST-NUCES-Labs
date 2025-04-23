class Employee:
    def __init__(self, salary):
        self.salary = salary
        self._increment = 1.1  # default increment

    @property
    def increment(self):
        return self._increment

    @increment.setter
    def increment(self, value):
        if self.salary < 50000:
            self._increment = 1.2
        else:
            self._increment = value

    @property
    def salaryAfterIncrement(self):
        return self.salary * self._increment
