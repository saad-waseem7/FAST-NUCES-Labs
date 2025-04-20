def check_for_python(log_file_path):
    with open(log_file_path, "r") as log_file:
        log_content = log_file.read()
    if "python" in log_content.lower():
        print(f"The log file '{log_file_path}' contains the word 'python'.")
        return True
    else:
        print(f"The log file '{log_file_path}' does not contain the word 'python'.")
        return False


log_file = "E:\\Python_Course\\Chapter#9\\my_Log.txt"

with open(log_file, "w") as f:
    f.write("This is a test log file.  It contains the word Python.\n" * 10)
contains_python = check_for_python(log_file)

if contains_python:
    print("The program found 'python' in the log file.")
else:
    print("The program did not find 'python' in the log file.")
