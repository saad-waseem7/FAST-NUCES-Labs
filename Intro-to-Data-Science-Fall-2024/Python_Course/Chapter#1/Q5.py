# Question 5:

import os

test_path = "E:/VS Work/Temp/Python_Course/Day#1"
contents = os.listdir(test_path)

print("Contents of the directory:")
for item in contents:
    print(item)