my_comment = input("Enter your comment: ").lower()

spam_keywords = ["make a lot of money", "buy now", "subscribe this", "click this"]

is_spam = False
for keyword in spam_keywords:
    if keyword in my_comment:
        is_spam = True
        break

if is_spam:
    print("This is a spam comment.")
else:
    print("This is not a spam comment.")
