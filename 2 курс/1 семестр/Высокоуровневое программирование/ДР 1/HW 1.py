from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPainter, QColor, QBrush
import sys
from Interface import *
import matplotlib.pyplot as plt
import math

class MyWin(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.activatedLight = 0
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
                  
        self.ui.GraphButton.clicked.connect(self.PressGraph)

        self.ui.RedButton.toggled.connect(self.PressRed)
        self.ui.YellowButton.toggled.connect(self.PressYellow)
        self.ui.GreenButton.toggled.connect(self.PressGreen)

        self.ui.HelpButton.clicked.connect(self.PressHelp)

    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        self.drawRectangles(qp)
        qp.end()

    def drawRectangles(self, qp):
        col = QColor(0, 0, 0)
        col.setNamedColor('#d4d4d4')
        qp.setPen(col)

        if self.activatedLight == 0:
            qp.setBrush(QColor(255, 255, 255))
            qp.drawRect(160, 60, 60, 60)
            
            qp.setBrush(QColor(255, 255, 255))
            qp.drawRect(160, 120, 60, 60)
            
            qp.setBrush(QColor(255, 255, 255))
            qp.drawRect(160, 180, 60, 60)
            
        elif self.activatedLight == 1:
            qp.setBrush(QColor(230, 0, 0))
            qp.drawRect(160, 60, 60, 60)
            
            qp.setBrush(QColor(255, 255, 255))
            qp.drawRect(160, 120, 60, 60)
            
            qp.setBrush(QColor(255, 255, 255))
            qp.drawRect(160, 180, 60, 60)

        elif self.activatedLight == 2:
            qp.setBrush(QColor(255, 255, 255))
            qp.drawRect(160, 60, 60, 60)
            
            qp.setBrush(QColor(247, 231, 0))
            qp.drawRect(160, 120, 60, 60)
            
            qp.setBrush(QColor(255, 255, 255))
            qp.drawRect(160, 180, 60, 60)

        elif self.activatedLight == 3:
            qp.setBrush(QColor(255, 255, 255))
            qp.drawRect(160, 60, 60, 60)
            
            qp.setBrush(QColor(255, 255, 255))
            qp.drawRect(160, 120, 60, 60)
            
            qp.setBrush(QColor(0, 171, 17))
            qp.drawRect(160, 180, 60, 60)
                
    def PressGraph(self):
        x1 = [n/10 for n in range(-40, 0)]
        x2 = [n/10 for n in range(1, 41)]
        y1 = [abs(math.cos(2*n)*math.sin(3*n))/math.sin(n) for n in x1]
        y2 = [abs(math.cos(2*n)*math.sin(3*n))/math.sin(n) for n in x2]
        ax = [0, 0]
        ay = [-4, 4]
    
        plt.text(0.5, 3.5, "y = |cos(2x)sin(2x)|/sin(x)")
        plt.plot(x1, y1, x2, y2, ax, ay, '--')
        plt.show()

    def PressRed(self):
        button = self.sender()
        if button.isChecked():
            self.activatedLight = 1
            self.update()

    def PressYellow(self):
        button = self.sender()
        if button.isChecked():
            self.activatedLight = 2
            self.update()

    def PressGreen(self):
        button = self.sender()
        if button.isChecked():
            self.activatedLight = 3
            self.update()

    def PressHelp(self):
        message = QtWidgets.QMessageBox()
        message.setIcon(QtWidgets.QMessageBox.Information)
        message.setText("Обращение за справкой")
        message.setWindowTitle("Справка")
        message.exec_()

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    myapp = MyWin()
    myapp.show()
    sys.exit(app.exec_())
