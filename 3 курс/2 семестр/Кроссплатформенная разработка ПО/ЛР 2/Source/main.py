from Windows.MainWindow import MainWindow
from PyQt5 import QtWidgets
import sys

app = QtWidgets.QApplication([])
application = MainWindow()
application.show()

sys.exit(app.exec())