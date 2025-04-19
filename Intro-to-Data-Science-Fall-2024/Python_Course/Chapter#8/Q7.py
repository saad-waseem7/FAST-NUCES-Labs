def remove_and_strip(words, remove_word):
    new_list = []

    for word in words:
        word = word.strip()  
        if word != remove_word:  
            new_list.append(word)  

    return new_list

words = ["  apple", "banana  ", "  cherry  ", "banana"]
word_to_remove = "banana"

result = remove_and_strip(words, word_to_remove)

print("Updated list:", result)
