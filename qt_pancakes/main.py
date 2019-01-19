from math import sqrt, pi
from sys import exit, argv
import sys
from Point import Point
from Pan import Pan
from Pancake import Pancake
from PyQt4 import QtGui, QtCore
from PyQt4.QtGui import *
from PyQt4.QtCore import *

'''
Todo:
 * Не рисовать блины вне сковороды
'''

WINDOW_W = 800
WINDOW_H = 600
PAN_X = 300
PAN_Y = 300

class MainWindow(QtGui.QWidget):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.initUI()

        filename = argv[1]
        fin = open(filename, 'r')
        lines = fin.readlines()
        self.PAN_radius = float(lines[0].split()[1])
        self.PAN_work = float(lines[1].split()[1])
        self.DOUGH_volume = float(lines[2].split()[1])
        self.PANCAKES_count = int(lines[3].split()[1])
        self.PANCAKES_height = float(lines[4].split()[1])
        self.PANCAKES_volumes = []
        self.PANCAKES_centers = []
        for i in range(self.PANCAKES_count):
            self.PANCAKES_volumes.append(float(lines[i+5]))
        for i in range(self.PANCAKES_count):
            self.PANCAKES_centers.append([float(x) for x in lines[i + 5 + self.PANCAKES_count].split()])
        fin.close()
        print(self.PANCAKES_volumes)
        print(self.PANCAKES_centers)
        self.currentPancake = 0 # номер текущего блина (независимо от текущей сковороды)
        self.numberOfPans = 0 # количество использованных сковородок
        self.perfect = 0 # количество идеальных блинов

        self.currentPanNumber = 1
        self.currentPan = Pan(Point(PAN_X, PAN_Y), self.PAN_radius, self.PAN_work)
        self.allPans = [self.currentPan]


    def initUI(self):
        self.setGeometry(100, 100, WINDOW_W, WINDOW_H)
        self.setWindowTitle('Pancakes')

        self.buttonN = QtGui.QPushButton('Next', self)
        self.buttonN.clicked.connect(self.handleButtonNext)
        self.buttonP = QtGui.QPushButton('Prev', self)
        self.buttonP.clicked.connect(self.handleButtonPrev)
        self.buttonN.move(680, 550)
        self.buttonP.move(580, 550)

        labelFont = QtGui.QFont("Djvu sans", 12)

        self.label1 = QtGui.QLabel(self)
        self.label1.setText("Всего блинов: ")
        self.label1.setFont(labelFont)
        self.label1.move(580, 40)
        self.labelAll = QtGui.QLabel(self)
        self.labelAll.setText("000")
        self.labelAll.setFont(labelFont)
        self.labelAll.move(730, 40)

        self.label2 = QtGui.QLabel(self)
        self.label2.setText("Идеальных: ")
        self.label2.setFont(labelFont)
        self.label2.move(580, 60)
        self.labelPerfect = QtGui.QLabel(self)
        self.labelPerfect.setText("000")
        self.labelPerfect.setFont(labelFont)
        self.labelPerfect.move(730, 60)

        self.label3 = QtGui.QLabel(self)
        self.label3.setText("Сковорода: ")
        self.label3.setFont(labelFont)
        self.label3.move(580, 80)
        self.labelPan = QtGui.QLabel(self)
        self.labelPan.setText("000")
        self.labelPan.setFont(labelFont)
        self.labelPan.move(730, 80)

        self.label4 = QtGui.QLabel(self)
        self.label4.setText("Блины: ")
        self.label4.setFont(labelFont)
        self.label4.move(580, 120)

        self.labelPancakes = QtGui.QLabel(self)
        self.labelPancakes.setFixedSize(200, 200)
        self.labelPancakes.setAlignment(QtCore.Qt.AlignTop)
        self.labelPancakes.setFont(QtGui.QFont("Djvu sans", 8))
        self.labelPancakes.move(580, 140)

        self.labelMouse = QLabel(self)
        self.labelMouse.setFixedSize(100, 20)
        self.labelMouse.setFont(QtGui.QFont("Djvu sans", 8))
        self.labelMouse.move(10, 570)

        self.show()


    def mousePressEvent(self, QMouseEvent):
        currPos = str(QMouseEvent.pos())[14:]
        self.labelMouse.setText(currPos)


    def handleButtonNext(self):
        if self.currentPancake < self.PANCAKES_count:
            square = self.PANCAKES_volumes[self.currentPancake] / self.PANCAKES_height
            
            if self.currentPan.freespace < square:
                self.currentPan = Pan(Point(PAN_X, PAN_Y), self.PAN_radius, self.PAN_work)
                print("New pan")
                self.numberOfPans += 1
                self.currentPanNumber += 1
                self.allPans.append(self.currentPan)

            x = self.PANCAKES_centers[self.currentPancake][0]
            y = self.PANCAKES_centers[self.currentPancake][1]
            p = Point(x, y)
            
            if not self.currentPan.containsPoint(p):
                print("ERROR: Point is not in pan")
                w = QWidget()
                QtGui.QMessageBox.warning(w, 'Error', "Point is not in pan");
                exit()
            if square > self.currentPan.square * self.currentPan.work:
                print("ERROR: Pancake is too large")
                w = QWidget()
                QtGui.QMessageBox.warning(w, 'Error', "Pancake is too big");
                exit()
            
            for pancake in self.currentPan.pancakes:
                if pancake.containsPoint(p):
                    print(pancake)
                    print(p)
                    print((p.x - pancake.center.x)**2 + (p.y - pancake.center.y)**2)
                    print(pancake.radius**2)
                    print("ERROR: Center is in other pancake")
                    #QtGui.QMessageBox("ERROR: Center is in other pancake")
                    w = QWidget()
                    QtGui.QMessageBox.warning(w, 'Error', "Center is in other pancake");
                    exit()
            
            newPancake = Pancake(p, square, self.currentPan)
            if newPancake.isCircle:
                self.perfect += 1
            self.currentPan.pancakes.append(newPancake)
            self.currentPan.freespace -= newPancake.square
            self.currentPancake += 1

            self.update()
        else:
            print("No pancakes")


    def handleButtonPrev(self):
        if len(self.currentPan.pancakes) == 0:
            # if this is the first pan
            if self.currentPanNumber == 1:
                print("No pancakes and no pans")
                return
            else:
                print("Prev pan")
                self.currentPanNumber -= 1
                self.currentPan = self.allPans[self.currentPanNumber - 1]

        else:
            lastPancake = self.currentPan.pancakes.pop() # delete last pancake
            self.currentPan.freespace += lastPancake.square
            if lastPancake.isCircle:
                self.perfect -= 1
            self.currentPancake -= 1

        self.update()


    def paintEvent(self, e):
        self.labelAll.setText(str(self.currentPancake))
        self.labelPerfect.setText(str(self.perfect))
        self.labelPan.setText(str(self.currentPanNumber))
        pancakes_text = ""
        for pancake in self.currentPan.pancakes:
            pancakes_text += str(pancake) + '\n'
        self.labelPancakes.setText(pancakes_text)

        qp = QPainter()
        qp.begin(self)
        self.drawPancakes(qp)


    def drawPancakes(self, qp):

        # draw pan
        qp.setBrush(QtGui.QColor(255, 177, 117))
        pan_x = self.currentPan.center.x - self.currentPan.radius
        pan_y = self.currentPan.center.y - self.currentPan.radius
        qp.drawEllipse(pan_x, pan_y, self.currentPan.radius * 2, self.currentPan.radius * 2)

        # draw pancakes
        # TO DO!
        # qp.setCompositionMode(QPainter.CompositionMode_DestinationOver)
        # qp.setRenderHints(QPainter.HighQualityAntialiasing)
        for pancake in self.currentPan.pancakes[::-1]:
            # print("draw")
            real_x = pancake.center.x - pancake.radius
            real_y = pancake.center.y - pancake.radius
            circleForPancake = QtGui.QGraphicsEllipseItem(real_x, real_y, pancake.radius * 2, pancake.radius * 2)
            
            myPen = QtGui.QPen()
            myPen.setWidth(2)
            myPen.setBrush(QtGui.QColor(255, 135, 0))
            qp.setPen(myPen)
            
            if pancake.isCircle:
                circleForPancake.setBrush(QtGui.QColor(255, 213, 0))
            else:
                circleForPancake.setBrush(QtGui.QColor(255, 232, 115))

            circleForPancake.setPen(myPen)
            circleForPancake.paint(qp, QtGui.QStyleOptionGraphicsItem())


        # draw border of pan
        myPen = QtGui.QPen()
        myPen.setWidth(3)
        myPen.setBrush(QtGui.QColor(166, 74, 0))
        qp.setPen(myPen)
        qp.setBrush(QtCore.Qt.NoBrush)
        qp.drawEllipse(pan_x, pan_y, self.currentPan.radius * 2, self.currentPan.radius * 2)

def main():
    app = QtGui.QApplication(sys.argv)
    ex = MainWindow()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()




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
