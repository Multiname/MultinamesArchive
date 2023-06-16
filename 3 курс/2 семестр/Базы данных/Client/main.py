from Windows.MainWindow import MainWindow
from Windows.LoginWindow import LoginWindow
from PyQt5 import QtWidgets
import sys

app = QtWidgets.QApplication([])

isExited = True
while isExited:
    application = LoginWindow()
    application.exec_()

    if not application.isReadyForClose:
        continue

    if application.isLogged:
        application = MainWindow(
            application.developerLogin,
            application.developerName,
            application.developerTag,
            application.token
        )
        
        application.show()
        app.exec()
        isExited = application.isExited
    else:
        isExited = False