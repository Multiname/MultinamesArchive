import sys
from PyQt5.QtCore import pyqtSignal, QObject
from PyQt5.QtWidgets import QMessageBox
from PyQt5.QtWidgets import QApplication, QLabel
from PyQt5.QtWidgets import QMainWindow, QPushButton, QRadioButton, QHBoxLayout

import matplotlib.pyplot as plt
import math

class Communicate(QObject):
    closeApp = pyqtSignal()

class Example(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        btn1 = QPushButton('Build the graph', self)
        btn1.move(30, 30)
        btn1.clicked.connect(btn1_clicked)

        layout = QHBoxLayout()
        self.rb1 = QRadioButton("Button1")
        self.rb1.setChecked(True)
        #rb1.move(30, 35)
        layout.addWidget(self.rb1)

        rb2 = QRadioButton("Button2")
        rb2.setChecked(False)
        rb2.move(30, 40)
        
        self.setMinimumSize(300, 300)  

def btn1_clicked():
    x1 = [n/10 for n in range(-40, 0)]
    x2 = [n/10 for n in range(1, 41)]
    y1 = [abs(math.cos(2*n)*math.sin(3*n))/math.sin(n) for n in x1]
    y2 = [abs(math.cos(2*n)*math.sin(3*n))/math.sin(n) for n in x2]
    ax = [0, 0]
    ay = [-4, 4]
    
    plt.text(0.5, 3.5, "y = |cos(2x)sin(2x)|/sin(x)")
    plt.plot(x1, y1, x2, y2, ax, ay, '--')
    plt.show()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    ex.show()
    sys.exit(app.exec_())
