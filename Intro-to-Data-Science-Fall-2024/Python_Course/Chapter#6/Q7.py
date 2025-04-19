def check_for_harry(post):
    post_lower = post.lower()
    return "harry" in post_lower

text = input("Enter the post: ")
if check_for_harry(text):
    print("The post is talking about Harry.")
else:
    print("The post is not talking about Harry.")
