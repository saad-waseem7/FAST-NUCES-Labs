def calculate_grade(marks):
    if 90 <= marks <= 100:
        return "Ex"
    elif 80 <= marks < 90:
        return "A"
    elif 70 <= marks < 80:
        return "B"
    elif 60 <= marks < 70:
        return "C"
    elif 50 <= marks < 60:
        return "D"
    elif marks < 50 and marks >= 0:
        return "F"
    else:
        return "Invalid Input"


try:
    marks = int(input("Enter the student's marks: "))
    if 0 <= marks <= 100:
        grade = calculate_grade(marks)
        print(f"The grade for {marks} is: {grade}")
    else:
        print("Invalid Input: Marks should be between 0 and 100.")
except ValueError:
    print("Invalid Input: Please enter a valid integer for marks.")
