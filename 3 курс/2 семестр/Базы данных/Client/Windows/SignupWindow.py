from PyQt5 import QtWidgets, QtCore, QtGui
from Widgets.SignupWidget import Ui_SignupWidget
import requests
from PyQt5.QtGui import QIcon

class SignupWindow(QtWidgets.QDialog):
    def __init__(self, loginWindow):
        super(SignupWindow, self).__init__()
        self.ui = Ui_SignupWidget()
        self.ui.setupUi(self)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.loginWindow = loginWindow
        self.ui.signupPushButton.clicked.connect(self.Signup)

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        #self.loginWindow.show()
        return super().closeEvent(a0)
    
    def Signup(self):
        response = requests.post('http://localhost:5165/Signup', json={
            'name': self.ui.nameLineEdit.text(),
            'login': self.ui.loginLineEdit.text(),
            'password': self.ui.passwordLineEdit.text()
        })

        if response.status_code == 400:
            self.ui.loginLineEdit.setStyleSheet("QLineEdit { background-color: red; }")
            return 
        
        if response.status_code == 200:
            self.close()