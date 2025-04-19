# Storing & fruit_list in a list by user

fruit_list = []
for i in range(7):
    fruit = input("Enter the name of a fruit: ")
    fruit_list.append(fruit)

print("You have entered the following fruit_list:")
for fruit in fruit_list:
    print(fruit)
