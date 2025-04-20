def replace_donkey(filename):
    with open(filename, "r") as file:
        file_content = file.read()

    updated_content = file_content.replace("Donkey", "#####")

    with open(filename, "w") as file:
        file.write(updated_content)
    print(f"Successfully replaced 'Donkey' with '#####' in '{filename}'")


path = "E:\\Python_Course\\Chapter#9\\censored_File.txt"
replace_donkey(path)
