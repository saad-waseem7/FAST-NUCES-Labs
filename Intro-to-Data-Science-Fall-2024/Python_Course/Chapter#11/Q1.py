class Vector2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Vector3D(Vector2D):
    def __init__(self, x, y, z):
        super().__init__(x, y)
        self.z = z
