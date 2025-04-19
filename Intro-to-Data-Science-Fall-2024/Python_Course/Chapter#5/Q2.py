numbers = []

print("Enter 8 numbers:")
for i in range(8):
    num = int(input(f"Number {i+1}: "))
    numbers.append(num)

unique_numbers = set(numbers)

print("Unique numbers are:")
for num in unique_numbers:
    print(num)
