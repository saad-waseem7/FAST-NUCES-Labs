from functools import reduce

numbers = [5, 12, 7, 25, 3, 18]
maximum = reduce(lambda a, b: a if a > b else b, numbers)

print("Maximum number is:", maximum)
