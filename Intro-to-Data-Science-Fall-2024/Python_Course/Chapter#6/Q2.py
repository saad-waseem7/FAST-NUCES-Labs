subject_1 = float(input("Enter marks for Subject 1: "))
subject_2 = float(input("Enter marks for Subject 2: "))
subject_3 = float(input("Enter marks for Subject 3: "))

total_marks = subject_1 + subject_2 + subject_3
percentage = (total_marks / 300) * 100

if percentage >= 40 and subject_1 >= 33 and subject_2 >= 33 and subject_3 >= 33:
    print("The student has passed.")
else:
    print("The student has failed.")
