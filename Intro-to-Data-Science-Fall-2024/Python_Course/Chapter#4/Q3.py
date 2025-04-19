my_tuple = (1, 2)
print("Original:", my_tuple)

try:
  my_tuple[0] = 5  # Trying to change it!
except TypeError:
  print("Can't change tuples!")

print("Still the same:", my_tuple)