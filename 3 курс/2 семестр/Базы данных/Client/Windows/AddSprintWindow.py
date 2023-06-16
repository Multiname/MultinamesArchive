from PyQt5 import QtWidgets, QtCore
from Widgets.AddSprintWidget import Ui_AddSprintWidget
import requests
from PyQt5.QtGui import QIcon

class AddSprintWindow(QtWidgets.QDialog):
    def __init__(self, projectId, token):
        super(AddSprintWindow, self).__init__()
        self.ui = Ui_AddSprintWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.projectId = projectId
        self.token = token

        self.isCreated = False

        self.ui.createPushButton.clicked.connect(self.Confirm)

    def Confirm(self):
        response = requests.post('http://localhost:5165/AddSprint', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "name": self.ui.nameLineEdit.text(),
            "projectId": self.projectId,
            "startDate": self.ui.startDateEdit.text(),
            "endDate": self.ui.endDateEdit.text()
        })

        if response.status_code == 200:
            self.isCreated = True
            self.close()