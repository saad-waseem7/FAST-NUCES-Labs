username = input("Enter your username: ")
userName_length = len(username)
if userName_length < 10:
    print("Username is less than 10 characters")
elif userName_length > 10:
    print("Username is more than 10 characters")
else:
    print("Username is exactly 10 characters")
