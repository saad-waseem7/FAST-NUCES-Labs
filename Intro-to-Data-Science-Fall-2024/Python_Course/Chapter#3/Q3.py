# Program to detect double space in string

def double_space_detector(string):
    if "  " in string:
        return True
    else:
        return False


test_string = "This  is a test string with double spaces."
print(f"Original string: {test_string}")
print(f"Contains double spaces: {double_space_detector(test_string)}")
