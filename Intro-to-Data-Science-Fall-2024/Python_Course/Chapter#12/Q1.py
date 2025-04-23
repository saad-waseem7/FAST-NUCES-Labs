filepath_1="E:\\Python_Course\\Chapter#12\\File_1.txt"
filepath_2="E:\\Python_Course\\Chapter#12\\File_2.txt"
filepath_3="E:\\Python_Course\\Chapter#12\\File_3.txt"

with open(filepath_1) as f1, open(filepath_2) as f2, open(filepath_3) as f3:
    lines1 = f1.readlines()
    lines2 = f2.readlines()
    lines3 = f3.readlines()

if not lines1 or not lines2 or not lines3:
    print("Error: One or more files could not be opened.")
