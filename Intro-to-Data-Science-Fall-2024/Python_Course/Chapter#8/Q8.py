def print_table(tableNum):
    for i in range(1, 11):
        print(f"{tableNum} x {i} = {tableNum * i}")

def get_valid_number(prompt):
    while True:
        number_str = input(prompt)
        try:
            number = int(number_str)
            return number
        except ValueError:
            print("Invalid input. Please enter a valid integer.")

inNum = get_valid_number("Enter a number to print its table: ")
print_table(inNum)
