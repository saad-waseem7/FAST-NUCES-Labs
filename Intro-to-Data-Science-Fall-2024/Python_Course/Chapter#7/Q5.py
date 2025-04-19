# Sum of first n natural numbers

def sum_of_n(number):
    if number < 1:
        return 0
    else:
        return number + sum_of_n(number - 1)

def get_valid_number(prompt):
    while True:
        number_str = input(prompt)
        try:
            number = int(number_str)
            return number
        except ValueError:
            print("Invalid input. Please enter a valid integer.")

inputNumber = get_valid_number("Enter a positive integer: ")
sum_result = sum_of_n(inputNumber)
print(f"The sum of the first {inputNumber} natural numbers is: {sum_result}")
