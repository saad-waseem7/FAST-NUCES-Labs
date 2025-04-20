def wipe_file_content(filename):
    with open(filename, 'w') as f:
        f.write('')
    print(f"Content of file '{filename}' has been wiped.")

file_path = "E:\\Python_Course\\Chapter#9\\my_Log.txt"

wipe_file_content(file_path)
with open(file_path, 'r') as f:
    content = f.read()
    if not content:
        print(f"File '{file_path}' is empty.")
    else:
        print(f"File '{file_path}' still has content: '{content}'")
