class Vector:
    def __init__(self, components):
        self.components = components

    def __add__(self, other):
        result = []
        for i in range(len(self.components)):
            result.append(self.components[i] + other.components[i])
        return Vector(result)

    def __mul__(self, other):
        dot_product = 0
        for i in range(len(self.components)):
            dot_product += self.components[i] * other.components[i]
        return dot_product

    def __str__(self):
        return str(self.components)

v1 = Vector([1, 2, 3])
v2 = Vector([4, 5, 6])

print("v1 + v2 =", v1 + v2)  
print("v1 * v2 =", v1 * v2)  
