tableNumber = int(input("Enter a number to print its table in reverse: "))

for i in range(10, 0, -1):
    print(f"{tableNumber} x {i} = {tableNumber * i}")
