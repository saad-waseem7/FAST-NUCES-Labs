numbers = [10, 23, 45, 66, 75, 89, 100, 7]
div_by_5 = list(filter(lambda x: x % 5 == 0, numbers))

print("Numbers divisible by 5:", div_by_5)
