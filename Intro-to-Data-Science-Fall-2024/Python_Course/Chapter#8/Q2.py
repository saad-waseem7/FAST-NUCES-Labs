def celsius_to_fahrenheit(celsius):
    return (celsius * 9/5) + 32

temp_cel = float(input("Enter temperature in Celsius: "))
temp_far = celsius_to_fahrenheit(temp_cel)
print(f"Temperature in Fahrenheit: {temp_far}")
