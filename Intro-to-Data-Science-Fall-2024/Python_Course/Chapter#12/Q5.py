num = int(input("Enter a number: "))
table = [num * i for i in range(1, 11)]

path= "E:\\Python_Course\\Chapter#12\\fileTables.txt"

with open(path, "w") as file:
    for i in range(1, 11):
        file.write(f"{num} x {i} = {num * i}\n")

print("Multiplication table saved to fileTables.txt")
