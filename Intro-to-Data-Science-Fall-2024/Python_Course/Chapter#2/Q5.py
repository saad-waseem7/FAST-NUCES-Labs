# Finding average of two numbers.


def get_valid_number(prompt):
    while True:
        number_str = input(prompt)
        try:
            number = float(number_str)
            return number
        except ValueError:
            print("Invalid input. Please enter a valid number.")


number_first = get_valid_number("Enter first number: ")
number_second = get_valid_number("Enter second number: ")

average = (number_first + number_second) / 2
print(f"The average of {number_first} and {number_second} is: {average}")
