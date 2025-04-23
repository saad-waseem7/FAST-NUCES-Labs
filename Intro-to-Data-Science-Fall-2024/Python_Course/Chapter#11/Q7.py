class Vector:
    def __init__(self, components):
        self.components = components

    def __add__(self, other):
        result = []
        for i in range(len(self.components)):
            result.append(self.components[i] + other.components[i])
        return Vector(result)

    def __mul__(self, other):
        result = 0
        for i in range(len(self.components)):
            result += self.components[i] * other.components[i]
        return result

    def __len__(self):
        return len(self.components)

    def __str__(self):
        output = ""
        for i in range(len(self.components)):
            output += str(self.components[i]) + "e" + str(i + 1)
            if i != len(self.components) - 1:
                output += " + "
        return output

v1 = Vector([1, 2, 3])
v2 = Vector([4, 5, 6])

print("v1:", v1)
print("v2:", v2)
print("v1 + v2:", v1 + v2)
print("v1 . v2:", v1 * v2)
print("Length of v1:", len(v1))
