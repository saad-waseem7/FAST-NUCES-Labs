def inches_to_cm(inches):
    return inches * 2.54

def get_valid_number(prompt):
    while True:
        number_str = input(prompt)
        try:
            number = int(number_str)
            return number
        except ValueError:
            print("Invalid input. Please enter a valid integer.")

inch= get_valid_number("Enter length in inches: ")
cm = inches_to_cm(inch)
print(f"{inch} inches is equal to {cm} cm")
