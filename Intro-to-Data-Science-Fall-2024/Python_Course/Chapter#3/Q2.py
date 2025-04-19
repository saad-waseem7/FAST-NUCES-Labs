import datetime

name = input("Enter your name: ")
current_date = datetime.date.today()

letter = f"Dear {name},\nYou are selected!\n{current_date}"
print(letter)
