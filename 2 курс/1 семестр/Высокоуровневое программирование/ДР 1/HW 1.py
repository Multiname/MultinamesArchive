from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPainter, QColor, QBrush
import sys
from Interface import *

class MyWin(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
                  
        self.ui.pushButton.clicked.connect(self.buttonpress)

    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        self.drawRectangles(qp)
        qp.end()

    def drawRectangles(self, qp):
        col = QColor(0, 0, 0)
        col.setNamedColor('#d4d4d4')
        qp.setPen(col)

        qp.setBrush(QColor(200, 0, 0))
        qp.drawRect(150, 30, 60, 60)

        qp.setBrush(QColor(255, 80, 0, 160))
        qp.drawRect(150, 90, 60, 60)

        qp.setBrush(QColor(25, 0, 90, 200))
        qp.drawRect(150, 150, 60, 60)
                
    def buttonpress(self):
        print("OK")

if __name__=="__main__":
    app = QtWidgets.QApplication(sys.argv)
    myapp = MyWin()
    myapp.show()
    sys.exit(app.exec_())
