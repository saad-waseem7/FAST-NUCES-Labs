with open("E:\\Python_Course\\Chapter#9\\Poem.txt", "r") as f:
    text = f.read()
    print(text)


if "twinkle" in text.lower():
    print("The word 'twinkle' is present in the file.")
else:
    print("The word 'twinkle' is not present in the file.")
