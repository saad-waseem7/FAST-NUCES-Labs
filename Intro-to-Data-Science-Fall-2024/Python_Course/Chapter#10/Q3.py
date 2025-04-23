class MyClass:
    a = 10

obj = MyClass()

print(f"Class attribute MyClass.a before object assignment: {MyClass.a}")
print(f"Object attribute obj.a before object assignment: {obj.a}")

obj.a = 0

print(f"Class attribute MyClass.a after object assignment: {MyClass.a}")
print(f"Object attribute obj.a after object assignment: {obj.a}")
