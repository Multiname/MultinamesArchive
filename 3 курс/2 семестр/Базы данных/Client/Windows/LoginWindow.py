from PyQt5 import QtWidgets, QtCore
from PyQt5.QtGui import QIcon
from Widgets.LoginWidget import Ui_LoginWidget
from Windows.SignupWindow import SignupWindow
import requests

class LoginWindow(QtWidgets.QDialog):
    def __init__(self):
        super(LoginWindow, self).__init__()
        self.ui = Ui_LoginWidget()
        self.ui.setupUi(self)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.isLogged = False
        self.isReadyForClose = True

        self.ui.signupPushButton.clicked.connect(self.Signup)
        self.ui.loginPushButton.clicked.connect(self.Login)

        # print(requests.post('http://localhost:5165/F', json={
        #     'login': 'aboba',
        #     'password': 'bebra',
        #     'name': 'abobster',
        #     'tag': '48084'
        # }).content)

        # try:
        #     print(requests.get('http://localhost:5165/GetWeatherForecast', headers={'accept': 'text/plain'}, timeout=5).content)
        # except requests.exceptions.ConnectionError as e:
        #     print(e)

    def Signup(self):
        self.isReadyForClose = False
        self.signupWindow = SignupWindow(self)
        self.hide()
        self.signupWindow.exec_()

    def Login(self):
        response = requests.post('http://localhost:5165/Login', json={
            'login': self.ui.loginLineEdit.text(),
            'password': self.ui.passwordLineEdit.text()
        })

        if response.status_code == 200:
            self.developerLogin = response.json()['login']
            self.developerName = response.json()['name']
            self.developerTag = response.json()['tag']
            self.token = response.json()['token']
            self.isLogged = True
            self.close()

            # token = response.json()['token']
            # print(token)

            # response = requests.get('http://localhost:5165/F', headers={
            #     'Accept': 'application/json',
            #     "Authorization": "Bearer " + token
            # })

            # print(response.content)