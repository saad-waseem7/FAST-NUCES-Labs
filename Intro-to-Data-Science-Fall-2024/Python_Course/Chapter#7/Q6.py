# Factorial using Loop

def factorial(number):
    result = 1
    for i in range(1, number + 1):
        result *= i
    return result

def get_valid_number(prompt):
    while True:
        number_str = input(prompt)
        try:
            number = int(number_str)
            return number
        except ValueError:
            print("Invalid input. Please enter a valid integer.")


number = get_valid_number("Enter a positive integer: ")
factorial_result = factorial(number)
print(f"The factorial of {number} is: {factorial_result}")
