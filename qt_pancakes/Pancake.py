from math import sqrt, pi, sin, cos, ceil
import random
from Point import Point

class Pancake:
    def __init__(self, center, square, pan):
        self.center = center
        self.square = square
        self.pan = pan
        self.isCircle = True # имеет ли блин идеальную форму
        self.radius = sqrt(self.square/pi) # изначально мы не знаем реальный радиус
        self.testCircle() # узнаём, является ли блин идеальным по форме
        self.radius = self.countRadius() # если блин не идеальный, то его радиус изменится

    def __repr__(self):
        return "(%.1f, %.1f), S: %.1f, R: %.1f" % \
               (self.center.x, self.center.y, self.square, self.radius)

    # идеальная ли форма
    def testCircle(self):
        for pancake in self.pan.pancakes:
            if self.intersectTo(pancake) and pancake != self: # bugs
                self.isCircle = False
        if self.pan.intersectTo(self):
            self.isCircle = False

    # countRadius: Pancake self -> float radius
    def countRadius(self):
        if self.isCircle:
            return sqrt(self.square/pi)
        else:
            # Монте-Карло
            randomPoints = []
            countOfRandomPoints = 100000 # количество случайных точек
            # количество точек для получения круга
            countOfPointsInSelf = int(ceil(countOfRandomPoints * (self.square / self.pan.square)))
            # уже полученные точки, лежащие внутри self
            pointsInSelf = 0
            # генерируем случайные точки внутри круга-сковороды
            for i in range(countOfRandomPoints):
                t = 2 * pi * random.random()
                a = random.random()
                b = random.random()
                u = a + b
                if u > 1:
                    r = 2-u
                else:
                    r = u
                newPointX = self.pan.radius*r*cos(t) + self.pan.center.x
                newPointY = self.pan.radius*r*sin(t) + self.pan.center.y
                newPoint = Point(newPointX, newPointY)
                #print(newPoint)
                randomPoints.append(newPoint)

            # сортируем точки по расстоянию до центра self
            distToCenter = lambda p: p.distanceTo(self.center)
            randomPoints.sort(key = distToCenter)

            '''
            fout = open("data.txt","a")
            for p in randomPoints:
                print(p.x, p.y, file=fout)
            fout.close()
            '''

            # проверяем каждую точку:
            # если точка не лежит ни в одном из кругов,
            # то добавляем её к точкам, составляющим self
            result = -1
            for p in randomPoints:
                flag = True
                for pancake in self.pan.pancakes:
                    if pancake.containsPoint(p): flag = False

                if flag: pointsInSelf += 1
                # останавливаемся, если уже набрали нужное количество
                if pointsInSelf >= countOfPointsInSelf:
                    result = p.distanceTo(self.center)
                    # print(p, "%.3f" % result)
                    break

            return result


    # лежит ли точка внутри окружности блина
    def containsPoint(self, point):
        if ((point.x - self.center.x)**2 + (point.y - self.center.y)**2 <= self.radius**2):
            # print(point)
            # print((point.x - self.center.x)**2 + (point.y - self.center.y)**2)
            # print(self.radius**2)
            return True
        return False

    # пересечение окружности с окружностью другого блина
    # используется только для определения формы блина (идеальная или нет)
    def intersectTo(self, other):
        dx = self.center.x - other.center.x
        dy = self.center.y - other.center.y
        d = sqrt(dx**2 + dy**2)

        if d > (self.radius + other.radius):
            return False
        if d < abs(self.radius - other.radius):
            return False

        return True
