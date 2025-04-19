# Python program to find reminder when number is divided by Z


def get_valid_number(prompt):
    while True:
        number_str = input(prompt)
        try:
            number = float(number_str)
            return number
        except ValueError:
            print("Invalid input. Please enter a valid number.")


def find_remainder(number, Z):
    remainder = number % Z
    return remainder


number = get_valid_number("Enter a number: ")
Z = get_valid_number("Enter the divisor (Z): ")

remainder = find_remainder(number, Z)
print(f"The remainder when {number} is divided by {Z} is: {remainder}")
