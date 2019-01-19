import random
from math import sqrt, pi, sin, cos, ceil
from sys import exit, argv

'''
Mathematica:
* RegionIntersection
* RegionMeasure
'''

# просто точка
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return "Point(%.3f, %.3f)" % (self.x, self.y)
    
    # расстояние от точки до другой
    def distanceTo(self, other):
        return sqrt((self.x - other.x)**2 + (self.y - other.y)**2)


# сковорода
class Pan:
    def __init__(self, center, radius, work):
        self.center = center
        self.radius = radius
        self.square = pi * (radius**2)
        self.work = work # место, которое можно занимать блинами
        self.freespace = self.square * self.work

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
        if ((point.x - self.center.x)**2 + (point.y - self.center.y)**2 <= self.radius**2):
            return True
        return False



# блин    
class Pancake:
    def __init__(self, center, square):
        self.center = center
        self.square = square
        self.isCircle = True # имеет ли блин идеальную форму
        self.radius = sqrt(self.square/pi) # изначально мы не знаем реальный радиус
        self.testCircle() # узнаём, является ли блин идеальным по форме
        self.radius = self.countRadius() # если блин не идеальный, то его радиус изменится

    def __repr__(self):
        return "Pancake{(%.3f, %.3f), S: %.3f, R: %.3f, %r}" % (self.center.x, self.center.y, self.square, self.radius, self.isCircle)

    # идеальная ли форма
    def testCircle(self):
        global PAN
        global allPancakes
        for panc in allPancakes:
            if self.intersectTo(panc) and panc != self: # bugs
                self.isCircle = False
        if PAN.intersectTo(self): self.isCircle = False

    # countRadius: Pancake self -> float radius
    def countRadius(self):
        global PAN
        global allPancakes
        if self.isCircle:
            return sqrt(self.square/pi)
        else:
            # Монте-Карло
            randomPoints = []
            countOfRandomPoints = 100000 # количество случайных точек
            # количество точек для получения круга
            countOfPointsInSelf = int(ceil(countOfRandomPoints * (self.square / PAN.square)))
            # уже полученные точки, лежащие внутри self
            pointsInSelf = 0
            # генерируем случайные точки внутри круга-сковороды
            for i in range(countOfRandomPoints):
                t = 2 * pi * random.random()
                a = random.random()
                b = random.random()
                u = a + b
                if u > 1: r = 2-u
                else: r = u
                newPoint = Point(PAN.radius*r*cos(t), PAN.radius*r*sin(t))
                #print(newPoint)
                randomPoints.append(newPoint)

            # сортируем точки по расстоянию до центра self
            distToCenter = lambda p: p.distanceTo(self.center)
            randomPoints.sort(key=distToCenter)

            # проверяем каждую точку:
            # если точка не лежит ни в одном из кругов,
            # то добавляем её к точкам, составляющим self
            result = -1
            for p in randomPoints:
                flag = True
                for panc in allPancakes:
                    if panc.containsPoint(p): flag = False

                if flag: pointsInSelf += 1
                # останавливаемся, если уже набрали нужное количество
                if pointsInSelf >= countOfPointsInSelf:
                    result = p.distanceTo(self.center)
                    #print(p, "%.3f" % result)
                    break

            return result


    # лежит ли точка внутри окружности блина
    def containsPoint(self, point):
        if ((point.x - self.center.x)**2 + (point.y - self.center.y)**2 <= self.radius**2):
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


'''
Формат входного файла:

pan_R <радиус сковороды>
pan_Work <рабочая часть сковороды>
volume <объём теста>
amount <количество блинов>
height <высота блинов>
<объём теста для очередного блина>
. . .
<объём теста для очередного блина>
<центр очередного блина>
. . .
<центр очередного блина>
'''

filename = argv[1]
fin = open(filename, 'r')
lines = fin.readlines()
PAN_radius = float(lines[0].split()[1])
PAN_work = float(lines[1].split()[1])
DOUGH_volume = float(lines[2].split()[1])
PANCAKES_count = int(lines[3].split()[1])
PANCAKES_height = float(lines[4].split()[1])
PANCAKES_volumes = []
PANCAKES_centers = []
for i in range(PANCAKES_count):
    PANCAKES_volumes.append(float(lines[i+5]))
for i in range(PANCAKES_count):
    PANCAKES_centers.append([float(x) for x in lines[i+5+PANCAKES_count].split()])

fin.close()

#print(PANCAKES_volumes)
#print(PANCAKES_centers)


current = 0 # номер текущего блина
pans = 0 # количество использованных сковородок
perfect = 0 # количество идеальных блинов
while current < PANCAKES_count:
    PAN = Pan(Point(0.0, 0.0), PAN_radius, PAN_work)
    allPancakes = []
    #print("New pan")
    pans += 1
    square = PANCAKES_volumes[current] / PANCAKES_height
    while (current < PANCAKES_count) and (PAN.freespace >= square):
        square = PANCAKES_volumes[current] / PANCAKES_height
        x, y = PANCAKES_centers[current][0], PANCAKES_centers[current][1]
        p = Point(x, y)

        if not PAN.containsPoint(p):
            print("ERROR: Point is not in pan")
            exit()
        if square > PAN.square*PAN.work:
            print("ERROR: Pancake is too big")
            exit()
        for panc in allPancakes:
            if panc.containsPoint(p):
                print("ERROR: Center is in other pancake")
                exit()

        newPancake = Pancake(p, square)
        if newPancake.isCircle: perfect += 1
        allPancakes.append(newPancake)
        PAN.freespace -= newPancake.square
        current += 1
        # print(current)
    #print(allPancakes)

print("-----------")
print("Amount of pans:", pans)
print("Amount of perfect pancakes:", perfect)
