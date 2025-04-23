class Animals:
    def __init__(self, name):
        self.name = name

class Pets(Animals):
    pass

class Dog(Pets):
    def bark(self):
        print("Woof!")


dog1 = Dog("Buddy")
dog1.bark()  
