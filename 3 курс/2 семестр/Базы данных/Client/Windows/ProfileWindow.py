from PyQt5 import QtWidgets, QtCore
from Widgets.ProfileWidget import Ui_ProfileWidget
from Windows.EditPasswordWindow import EditPasswordWindow
from PyQt5.QtWidgets import QTableWidgetItem, QMessageBox, QHeaderView, QInputDialog
import requests
from PyQt5.QtGui import QIcon

class ProfileWindow(QtWidgets.QDialog):
    def __init__(self, developerLogin, developerName, developerTag, token):
        super(ProfileWindow, self).__init__()
        self.ui = Ui_ProfileWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.developerLogin = developerLogin
        self.developerName = developerName
        self.developerTag = developerTag
        self.token = token

        self.ui.loginLabel.setText(self.developerLogin)
        self.ui.nameLabel.setText(self.developerName)
        self.ui.tagLabel.setText(self.developerTag)

        self.ui.editNamePushButton.clicked.connect(self.EditDeveloperName)
        self.ui.editPasswordPushButton.clicked.connect(self.EditDeveloperPassword)

    def EditDeveloperName(self):
        newDeveloperName, ok = QInputDialog.getText(
            self,
            'Изменение имени',
            'Новое имя',
            flags=QtCore.Qt.WindowCloseButtonHint
        )

        if ok:
            response = requests.put('http://localhost:5165/EditDeveloperName', headers={
                'Accept': 'application/json',
                "Authorization": "Bearer " + self.token
            }, json={
                "name": newDeveloperName
            })

            if response.status_code == 200:
                self.developerName = newDeveloperName
                self.ui.nameLabel.setText(self.developerName)

    def EditDeveloperPassword(self):
        editPasswordWindow = EditPasswordWindow(self.token)
        editPasswordWindow.exec_()