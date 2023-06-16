from PyQt5 import QtWidgets, QtCore
from Widgets.EditPasswordWidget import Ui_EditPasswordWidget
from PyQt5.QtWidgets import QTableWidgetItem, QMessageBox, QHeaderView, QInputDialog
import requests
from PyQt5.QtGui import QIcon

class EditPasswordWindow(QtWidgets.QDialog):
    def __init__(self, token):
        super(EditPasswordWindow, self).__init__()
        self.ui = Ui_EditPasswordWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.token = token

        self.ui.submitPushButton.clicked.connect(self.Submit)

    def Submit(self):
        self.ui.oldPasswordLineEdit.setStyleSheet("QLineEdit { background-color: white; }")
        self.ui.passwordCheckLineEdit.setStyleSheet("QLineEdit { background-color: white; }")

        oldPassword = self.ui.oldPasswordLineEdit.text()
        newPassword = self.ui.newPasswordLineEdit.text()
        passwordCheck = self.ui.passwordCheckLineEdit.text()

        if newPassword != passwordCheck:
            self.ui.passwordCheckLineEdit.setStyleSheet("QLineEdit { background-color: red; }")
            return
        
        response = requests.put('http://localhost:5165/EditDeveloperPassword', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "oldPassword": oldPassword,
            "newPassword": newPassword
        })

        if response.status_code == 403:
            self.ui.oldPasswordLineEdit.setStyleSheet("QLineEdit { background-color: red; }")
            return
        
        if response.status_code == 200:
            self.close()