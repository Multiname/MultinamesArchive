from PyQt5 import QtGui, QtWidgets, QtCore, QtNetwork
from PyQt5.QtWidgets import QInputDialog
from Widgets.MainWidget import Ui_MainWidget
from Windows.ProfileWindow import ProfileWindow
from Windows.ProjectWindow import ProjectWindow
from Elements.ProjectElement import ProjectElement
import requests
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import QTimer, QUrl
import json

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, developerLogin, developerName, developerTag, token):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWidget()
        self.ui.setupUi(self)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.developerLogin = developerLogin
        self.developerName = developerName
        self.developerTag = developerTag
        self.token = token

        self.isExited = False
        self.isClosed = False
        self.projectElements = []

        self.ui.nameLabel.setText('Вы вошли как: ' + self.developerName)
        self.ui.exitPushButton.clicked.connect(self.Exit)
        self.ui.profilePushButton.clicked.connect(self.OpenProfile)
        self.ui.newProjectPushButton.clicked.connect(self.AddProject)

        self.LoadProjects()

        self.lastChanges = 0

        response = requests.get('http://localhost:5165/GetMembershipChanges', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            self.lastChanges = response.json()

        self.nam = QtNetwork.QNetworkAccessManager()
        self.nam.finished.connect(self.HandleChangesReply)
        QTimer.singleShot(1000, self.GetChanges)

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        self.isClosed = True
        return super().closeEvent(a0)

    def ClearProjects(self):
        self.projectElements.clear()

        layout = self.ui.projectsScrollAreaWidgetContentsVerticalLayout
        while layout.count():
            widget = layout.takeAt(0).widget()
            if widget is not None:
                widget.deleteLater()

    def LoadProjects(self):
        response = requests.get('http://localhost:5165/GetProjects', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            projects = response.json()

            self.ClearProjects()

            for i in range(len(projects)):
                self.projectElements.append(ProjectElement(
                    i,
                    projects[i]['name'],
                    projects[i]['owner'],
                    projects[i]['isOwner'],
                    self.ui.projectsScrollAreaWidgetContents,
                    lambda _, id=projects[i]['id'], io=projects[i]['isOwner']: self.OpenProject(id, io),
                    lambda _, id=projects[i]['id']: self.RemoveProject(id) if projects[i]['isOwner'] else self.LeaveProject(id)
                ))
                self.projectElements[i].SetElement(self.ui.projectsScrollAreaWidgetContentsVerticalLayout)

            spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
            self.ui.projectsScrollAreaWidgetContentsVerticalLayout.addItem(spacerItem)

    def OpenProject(self, projectId, isOwner):
        self.hide()
        self.projectWindow = ProjectWindow(self, self.token, projectId, isOwner)
        self.projectWindow.show()

    def Exit(self):
        self.isExited = True
        self.close()

    def OpenProfile(self):
        profileWindow = ProfileWindow(
            self.developerLogin,
            self.developerName,
            self.developerTag,
            self.token
        )
        profileWindow.exec_()

        if profileWindow.developerName != self.developerName:
            self.developerName = profileWindow.developerName
            self.ui.nameLabel.setText('Вы вошли как: ' + self.developerName)

    def AddProject(self):
        projectName, ok = QInputDialog.getText(
            self,
            'Новый проект',
            'Название проекта',
            flags=QtCore.Qt.WindowCloseButtonHint
        )

        if ok:
            response = requests.post('http://localhost:5165/AddProject', headers={
                'Accept': 'application/json',
                "Authorization": "Bearer " + self.token
            }, json={
                "name": projectName
            })

            if response.status_code == 200:
                self.LoadProjects()

    def RemoveProject(self, projectId):
        response = requests.post('http://localhost:5165/RemoveProject', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "projectId": projectId
        })

        if response.status_code == 200:
            self.LoadProjects()

    def LeaveProject(self, projectId):
        response = requests.post('http://localhost:5165/RemoveProjectDeveloper', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "projectId": projectId,
            "developerId": None
        })

        if response.status_code == 200:
            self.LoadProjects()

    def GetChanges(self):
        request = QtNetwork.QNetworkRequest(QUrl('http://localhost:5165/GetMembershipChanges'))
        
        request.setRawHeader(b'Accept', b'application/json')
        request.setRawHeader(b'Authorization', b'Bearer ' + self.token.encode('utf-8'))
        
        self.nam.get(request)

    def HandleChangesReply(self, reply):
        content = json.loads(str(reply.readAll(), 'utf-8'))

        if self.lastChanges != content:
            self.lastChanges = content
            self.LoadProjects()
        
        if not self.isClosed:
            QTimer.singleShot(1000, self.GetChanges)