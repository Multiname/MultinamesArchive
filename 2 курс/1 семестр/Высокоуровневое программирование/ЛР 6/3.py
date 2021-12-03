from PyQt5 import QtGui
from PyQt5.QtWidgets import QApplication, QMainWindow
import sys
from PyQt5.QtGui import QBrush, QPen,QPainter, QPolygon
from PyQt5.QtCore import QPoint, Qt

class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Boat')
        self.resize(500, 500)
        self.show()
 
    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setPen(QPen(Qt.black, 3, Qt.SolidLine))
        painter.setBrush(QBrush(QtGui.QColor(100, 70, 50)))
 
        painter.drawPolygon(QPolygon([
            QPoint(100, 300),
            QPoint(400, 300),
            QPoint(350, 400),
            QPoint(150, 400)]))

        painter.setBrush(QBrush(Qt.white))
        
        painter.drawPolygon(QPolygon([
            QPoint(250, 100),
            QPoint(350, 150),
            QPoint(350, 250),
            QPoint(250, 300)]))
        
App = QApplication(sys.argv)
window = Window()
sys.exit(App.exec())
