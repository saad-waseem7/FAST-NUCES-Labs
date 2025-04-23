a = int(input("Enter value of a: "))
b = int(input("Enter value of b: "))

try:
    result = a / b
    print("Result:", result)
except ZeroDivisionError:
    print("Result: infinite")
