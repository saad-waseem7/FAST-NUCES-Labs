import os

def rename_file(old_name, new_name):
    os.rename(old_name, new_name)
    print(f"File '{old_name}' successfully renamed to '{new_name}'")

current_file_name = "E:\\Python_Course\\Chapter#9\\orignal_File.txt"
new_file_name = "E:\\Python_Course\\Chapter#9\\by_python_rename.txt"
rename_file(current_file_name, new_file_name)