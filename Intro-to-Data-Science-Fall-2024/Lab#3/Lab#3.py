#!/usr/bin/env python
# coding: utf-8

# **Task#1**

# In[10]:


USD_TO_EUR_RATE = 0.84
EUR_TO_USD_RATE = 1.19
USD_TO_GBP_RATE = 0.76
GBP_TO_USD_RATE = 1.32

def convert_currency(amount, rate):
    try:
        return amount * rate
    except ZeroDivisionError:
        return "Error: Invalid exchange rate"

def main():
    while True:
        try:
            amount = float(input("Enter the amount to convert: "))
        except ValueError:
            print("Invalid input. Please enter a numeric value.")
            continue

        operation = input("Choose the conversion operation (USD to EUR, EUR to USD, USD to GBP, GBP to USD): ")

        if operation == "USD to EUR":
            result = convert_currency(amount, USD_TO_EUR_RATE)
        elif operation == "EUR to USD":
            result = convert_currency(amount, EUR_TO_USD_RATE)
        elif operation == "USD to GBP":
            result = convert_currency(amount, USD_TO_GBP_RATE)
        elif operation == "GBP to USD":
            result = convert_currency(amount, GBP_TO_USD_RATE)
        else:
            print("Invalid operation. Please choose a valid conversion operation.")
            continue

        if isinstance(result, str) and result.startswith("Error"):
            print(result)
        else:
            print(f"{amount} {operation.split(' to ')[0]} is equal to {result} {operation.split(' to ')[1]}")

        response = input("Would you like to perform another conversion? (yes/no): ")
        if response != "yes":
            break

if __name__ == "__main__":
    main()


# **Task#2**

# In[8]:


source_file_path = '/content/Poem.txt'
result_file_path = '/content/Reversed_Poem.txt'

with open(source_file_path, 'r') as source_file:
    lines = source_file.readlines()
reversed = lines[::-1]
with open(result_file_path, 'w') as result_file:
    result_file.writelines(reversed)

print("Reversed poem written to", result_file_path)


# **Task#3**

# In[7]:


def average_age(input_path, output_path):
    try:
        with open(input_path, 'r') as input_file:
            extract = []
            sum = 0
            num = 0
            for line in input_file:
                try:
                    age = float(line.strip())
                    sum += age
                    num += 1
                    extract.append(age)
                except ValueError:
                    print(f"Skipping non-numeric value '{line.strip()}'")
            if num == 0:
                print("No valid ages found in the input file")
                return

            average = sum / num

            try:
                with open(output_path, 'w') as output_file:
                    output_file.write(f"Average age: {average:.2f}\n")
                    print(f"Average age written to {output_path}")
            except PermissionError:
                print(f"Permission denied when writing to {output_path}")

    except FileNotFoundError:
        print(f"Input file '{input_path}' not found")

average_age('ages.txt', 'average_age.txt')


# **Task#4**

# In[9]:


import math
π = math.pi

class Cirlce:
    def __init__(self, radius):
        self.radius = radius

    def calculate_area(self):
        return π * self.radius ** 2

c1 = Cirlce(5)
print(c1.calculate_area())

