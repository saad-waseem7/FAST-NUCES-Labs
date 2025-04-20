# Check First
def check_for_python(log_file_path):
    with open(log_file_path, "r") as log_file:
        line_number = 0
        for line in log_file:
            line_number += 1
            if "python" in line.lower():
                return True, line_number
        return False, -1

log_file = "E:\\Python_Course\\Chapter#9\\my_Log.txt"

with open(log_file, "w") as f:
    f.write("This is a test log file.  It contains the word Python.\n" * 10)
contains_python, line_number = check_for_python(log_file)
if contains_python:
    print(f"'python' was found in the log file on line {line_number}.")
else:
    print("'python' was not found in the log file.")


# Check All
def check_for_python(log_file_path):
    line_numbers = []
    with open(log_file_path, "r") as log_file:
        line_number = 0
        for line in log_file:
            line_number += 1
            if "python" in line.lower():
                line_numbers.append(line_number)
        if line_numbers:
            return True, line_numbers
        else:
            return False, []

log_file = "E:\\Python_Course\\Chapter#9\\my_Log.txt"

with open(log_file, "w") as f:
    f.write("This is a test log file.  It contains the word Python.\n" * 10)
    f.write("Another line with Python here.\n")
    f.write("No python on this line.\n")
contains_python, line_numbers = check_for_python(log_file)

if contains_python:
    print(f"'python' was found in the log file on lines {line_numbers}.")
else:
    print("'python' was not found in the log file.")
