def censor_words(filename, words_to_censor):
    with open(filename, "r") as file:
        file_content = file.read()

    updated_content = file_content
    for word in words_to_censor:
        updated_content = updated_content.replace(word, "#####")

    with open(filename, "w") as file:
        file.write(updated_content)
    print(f"Successfully replaced censored words in '{filename}'")

path = "E:\\Python_Course\\Chapter#9\\censored_File.txt"
censor_words(path, ["Donkey", "Fool", "Idiot"])
