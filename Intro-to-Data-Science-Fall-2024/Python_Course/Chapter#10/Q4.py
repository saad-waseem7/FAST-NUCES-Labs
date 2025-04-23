import math

class Calculator:
    def square(self, number):
        return number * number

    def cube(self, number):
        return number * number * number

    def square_root(self, number):
        if number >= 0:
            return math.sqrt(number)
        else:
            return 0

    @staticmethod
    def greet():
        print("Hello!")

my_calculator = Calculator()

num = 4

square_of_num = my_calculator.square(num)
print(f"The square of {num} is: {square_of_num}")

cube_of_num = my_calculator.cube(num)
print(f"The cube of {num} is: {cube_of_num}")

sqrt_of_num = my_calculator.square_root(num)
print(f"The square root of {num} is: {sqrt_of_num}")

num2 = 25
square_root_of_num2 = my_calculator.square_root(num2)
print(f"The square root of {num2} is: {square_root_of_num2}")

Calculator.greet()
