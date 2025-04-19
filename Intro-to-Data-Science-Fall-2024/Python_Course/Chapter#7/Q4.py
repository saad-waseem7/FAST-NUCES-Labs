# Prime Check

def is_prime(num_to_check):
    if num_to_check <= 1:
        return False
    for i in range(2, int(num_to_check**0.5) + 1):
        if num_to_check % i == 0:
            return False
    return True

def get_valid_number(prompt):
    while True:
        number_str = input(prompt)
        try:
            number = float(number_str)
            return number
        except ValueError:
            print("Invalid input. Please enter a valid number.")

inputNumber = get_valid_number("Enter a number to check if it's prime: ")

if is_prime(inputNumber):
    print(f"{inputNumber} is a prime number.")
else:
    print(f"{inputNumber} is not a prime number.")
