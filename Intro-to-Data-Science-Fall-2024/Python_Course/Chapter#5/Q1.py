hindi_english = {
    "paani": "water",
    "roti": "bread",
    "kitab": "book",
    "dost": "friend",
    "ghar": "home",
}

word = input("Enter a Hindi word to translate: ")
translation = hindi_english.get(word)

if translation:
    print(f"The English translation of '{word}' is: {translation}")
else:
    print(f"Sorry, the word '{word}' is not in the dictionary.")
