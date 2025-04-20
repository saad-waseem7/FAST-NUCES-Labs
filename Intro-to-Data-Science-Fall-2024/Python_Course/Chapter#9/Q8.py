import shutil

def copy_file(source_file, destination_file):
    shutil.copy(source_file, destination_file)
    print(f"File '{source_file}' successfully copied to '{destination_file}'.")
    return True

source_file = "E:\\Python_Course\\Chapter#9\\copy_To.txt"
destination_file = "E:\\Python_Course\\Chapter#9\\Multiplication_Tables\\copy_To.txt"

with open(source_file, "w") as f:
    f.write("This is the content of the source file.\n")
    f.write("It will be copied.\n")
copy_successful = copy_file(source_file, destination_file)
if copy_successful:
    print("Copy operation was successful.")
else:
    print("Copy operation failed.")
