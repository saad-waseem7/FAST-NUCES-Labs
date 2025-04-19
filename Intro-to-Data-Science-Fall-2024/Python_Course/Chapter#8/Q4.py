def sum_natural(nat_Num):
    if nat_Num == 1:
        return 1
    else:
        return nat_Num + sum_natural(nat_Num - 1)


def get_valid_number(prompt):
    while True:
        number_str = input(prompt)
        try:
            number = int(number_str)
            return number
        except ValueError:
            print("Invalid input. Please enter a valid integer.")

inNum = get_valid_number("Enter a natural number: ")
print("Sum of first", inNum, "natural numbers is:", sum_natural(inNum))