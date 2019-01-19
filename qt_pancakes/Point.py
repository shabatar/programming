from math import sqrt

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return "Point(%.3f, %.3f)" % (self.x, self.y)

    # расстояние от точки до другой
    def distanceTo(self, other):
        return sqrt((self.x - other.x)**2 + (self.y - other.y)**2)
