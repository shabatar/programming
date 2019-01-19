from math import sqrt, pi

class Pan:
    def __init__(self, center, radius, work):
        self.center = center
        self.radius = radius
        self.square = pi * (radius**2)
        self.work = work  # место, которое можно занимать блинами
        self.freespace = self.square * self.work
        self.pancakes = [] # all pancakes in the pan

    # пересечение с блином
    def intersectTo(self, pancake):
        # просто проверяем окружности на пересечение
        dx = self.center.x - pancake.center.x
        dy = self.center.y - pancake.center.y
        d = sqrt(dx**2 + dy**2)

        if d > (self.radius + pancake.radius):
            return False
        if d < abs(self.radius - pancake.radius):
            return False

        return True

    # лежит ли точка внутри сковороды
    def containsPoint(self, point):
        if (point.x - self.center.x)**2 + (point.y - self.center.y)**2 <= self.radius**2:
            return True
        return False
