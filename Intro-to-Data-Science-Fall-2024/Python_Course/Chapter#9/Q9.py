def compare_files(file1_path, file2_path):
    with open(file1_path, "r") as f1:
        chunk1 = f1.read()
    with open(file2_path, "r") as f2:
        chunk2 = f2.read()
    if chunk1 == chunk2:
        print("Both files are identical.")
    else:
        print("Files are different.")


file1_path = "E:\\Python_Course\\Chapter#9\\copy_To.txt"
file2_path = "E:\\Python_Course\\Chapter#9\\Multiplication_Tables\\copy_To.txt"

compare_files(file1_path, file2_path)
