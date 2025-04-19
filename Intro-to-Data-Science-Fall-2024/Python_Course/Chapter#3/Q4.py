# Program to replace double spaces with single spaces

def replace_double_space(text):
    return text.replace("  ", " ")

test_string = "This  string has  double  spaces."
modified_string = replace_double_space(test_string)
print(f"Original string: {test_string}")
print(f"String with single spaces: {modified_string}")
