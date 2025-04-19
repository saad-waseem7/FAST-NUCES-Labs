# Program to print marks of 6 students in list

student_marks = []
for i in range(6):
    marks = int(input("Enter the marks of students: "))
    student_marks.append(marks)

student_marks.sort()
print("Sorted marks of students are: ", student_marks)
