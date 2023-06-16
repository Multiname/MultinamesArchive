from PyQt5 import QtWidgets, QtGui, QtCore, QtNetwork
from PyQt5.QtWidgets import QInputDialog
from Widgets.ProjectWidget import Ui_ProjectWidget
from Windows.BacklogWindow import BacklogWindow
from Windows.AddSprintWindow import AddSprintWindow
from Windows.EditSprintWindow import EditSprintWindow
from Windows.StoryWindow import StoryWindow
import requests
from Elements.MemberElement import MemberElement
from Elements.StoryElement import StoryElement
from PyQt5.QtGui import QIcon

from PyQt5.QtCore import QTimer, QUrl
import json

class ProjectWindow(QtWidgets.QMainWindow):
    def __init__(self, parent, token, projectId, isOwner):
        super(ProjectWindow, self).__init__(parent)
        self.ui = Ui_ProjectWidget(isOwner)
        self.ui.setupUi(self)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.storyBoardWidgetContents = [
            self.ui.toDoScrollAreaWidgetContents,
            self.ui.rejectedScrollAreaWidgetContents,
            self.ui.inProgressScrollAreaWidgetContents,
            self.ui.readyForTestingScrollAreaWidgetContents,
            self.ui.doneScrollAreaWidgetContents
        ]

        self.storyBoardLayouts = [
            self.ui.toDoScrollAreaWidgetContentsVerticalLayout,
            self.ui.rejectedScrollAreaWidgetContentsVerticalLayout,
            self.ui.inProgressScrollAreaWidgetContentsVerticalLayout,
            self.ui.readyForTestingScrollAreaWidgetContentsVerticalLayout,
            self.ui.doneScrollAreaWidgetContentsVerticalLayout
        ]

        self.token = token
        self.projectId = projectId
        self.isOwner = isOwner

        self.members = []
        self.memberElements = []
        self.sprints = []
        self.storyElements = []
        self.stories = []

        self.isReadyToClose = True
        self.isInitialized = False
        self.nameIsChanged = False
        self.isClosed = False

        self.selectedSprintId = None

        self.ui.backlogPushButton.clicked.connect(self.OpenBacklog)
        if self.isOwner:
            self.ui.renamePushButton.clicked.connect(self.EditProjectName)
            self.ui.addDeveloperPushButton.clicked.connect(self.AddMember)
            self.ui.editSprintPushButton.clicked.connect(self.EditSprint)

        self.LoadProjectName()
        self.LoadDevelopers()
        self.LoadSprints()

        self.lastChanges = {
            'name': 0,
            'members': 0,
            'sprints': 0,
            'boards': 0,
            'backlog': 0
        }

        response = requests.get('http://localhost:5165/GetProjectChanges?projectChanges=' + 
                                str(self.projectId), headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            changes = response.json()
            self.lastChanges['name'] = changes['name']
            self.lastChanges['members'] = changes['members']
            self.lastChanges['sprints'] = changes['sprints']
            self.lastChanges['boards'] = changes['boards']
            self.lastChanges['backlog'] = changes['backlog']

        self.nam = QtNetwork.QNetworkAccessManager()
        self.nam.finished.connect(self.HandleProjectChangesReply)
        QTimer.singleShot(1000, self.GetProjectChanges)

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        if self.isReadyToClose:
            self.parent().show()
            if self.nameIsChanged:
                self.parent().LoadProjects()
            self.isClosed = True
            return super().closeEvent(a0)
        a0.ignore()
        self.isReadyToClose = True
    
    def LoadProjectName(self):
        response = requests.get('http://localhost:5165/GetProject?projectId=' + str(self.projectId), headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            self.ui.projectLabel.setText(response.json()['projectName'])

    def ClearDevelopers(self):
        self.memberElements.clear()
        self.members.clear()

        layout = self.ui.developersScrollAreaWidgetContentsVerticalLayout
        while layout.count():
            widget = layout.takeAt(0).widget()
            if widget is not None:
                widget.deleteLater()

    def LoadDevelopers(self):
        response = requests.get('http://localhost:5165/GetProjectDevelopers?projectId=' + str(self.projectId), headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            if not response.json()['isMember']:
                self.close()
            
            self.ClearDevelopers()

            self.members = sorted(response.json()['developers'], key=lambda x: x['id'])

            for i in range(len(self.members)):
                self.memberElements.append(MemberElement(
                    i,
                    self.members[i]['name'],
                    self.members[i]['isOwner'],
                    self.ui.developersScrollAreaWidgetContents,
                    (lambda _, id=self.members[i]['id']: self.RemoveProjectDeveloper(id)) if self.isOwner else None
                ))
                self.memberElements[i].SetElement(self.ui.developersScrollAreaWidgetContentsVerticalLayout)

            spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
            self.ui.developersScrollAreaWidgetContentsVerticalLayout.addItem(spacerItem)

    def RemoveProjectDeveloper(self, developerId):
        response = requests.post('http://localhost:5165/RemoveProjectDeveloper', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "projectId": self.projectId,
            "developerId": developerId
        })

        if response.status_code == 200:
            #self.LoadDevelopers()
            pass

    def AddMember(self):
        tag, ok = QInputDialog.getText(
            self,
            'Новый участник',
            'Тег участника',
            flags=QtCore.Qt.WindowCloseButtonHint
        )

        if ok:
            response = requests.post('http://localhost:5165/AddProjectDeveloper', headers={
                'Accept': 'application/json',
                "Authorization": "Bearer " + self.token
            }, json={
                "tag": tag,
                "projectId": self.projectId
            })

            if response.status_code == 200:
                #self.LoadDevelopers()
                pass

    def OpenBacklog(self):
        self.backlogWindow = BacklogWindow(self, self.token, self.projectId, self.members, self.isOwner)
        self.isReadyToClose = False
        self.backlogWindow.exec_()

    def ClearSprints(self):
        if self.isInitialized:
            self.ui.sprintsComboBox.activated[int].disconnect(self.SelectSprint)

        self.isInitialized = True
        self.sprints.clear()
        self.ui.sprintsComboBox.clear()

    def LoadSprints(self, selectedIndex=None, selectedSprintId=None):
        self.ClearSprints()

        response = requests.get('http://localhost:5165/GetSprints?projectId=' + str(self.projectId), headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            self.sprints = sorted(response.json(), key=lambda x: x['id'])

            comboBox = self.ui.sprintsComboBox
            comboBox.addItems(list(map(lambda x: x['name'], self.sprints)))

            if self.isOwner:
                comboBox.addItem('Создать')

            if selectedIndex == None or selectedIndex >= len(self.sprints):
                self.selectedSprintIndex = len(self.sprints) - 1
                if self.selectedSprintIndex > -1:
                    self.selectedSprintId = self.sprints[self.selectedSprintIndex]['id']
                else:
                    self.selectedSprintId = None
            else:
                if selectedSprintId != None:
                    if self.sprints[selectedIndex]['id'] == selectedSprintId:
                        self.selectedSprintIndex = selectedIndex
                    else:
                        self.selectedSprintIndex = len(self.sprints) - 1
                        if self.selectedSprintIndex > -1:
                            self.selectedSprintId = self.sprints[self.selectedSprintIndex]['id']
                        else:
                            self.selectedSprintId = None
                else:
                    self.selectedSprintIndex = selectedIndex
                    self.selectedSprintId = self.sprints[self.selectedSprintIndex]['id']

            comboBox.setCurrentIndex(self.selectedSprintIndex)

            comboBox.activated[int].connect(self.SelectSprint)

            if self.selectedSprintIndex != -1 and self.selectedSprintIndex < len(self.sprints):
                self.ui.startDateLabel.setText(self.sprints[self.selectedSprintIndex]['startDate'])
                self.ui.endDateLabel.setText(self.sprints[self.selectedSprintIndex]['endDate'])

            if self.selectedSprintIndex != -1:
                self.LoadStories()

    def SelectSprint(self, index):
        if index == len(self.sprints):
            self.AddSprint()
            self.LoadSprints()
        else:
            self.LoadSprints(index)

    def AddSprint(self):
        self.addSprintWindow = AddSprintWindow(self.projectId, self.token)
        self.isReadyToClose = False
        self.addSprintWindow.exec_()

    def EditSprint(self):
        if self.selectedSprintIndex != -1:
            self.editSprintWindow = EditSprintWindow(self.projectId, self.sprints[self.selectedSprintIndex], self.token)
            self.isReadyToClose = False
            self.editSprintWindow.exec_()

            # if self.editSprintWindow.isChanged:
            #     if self.editSprintWindow.isRemoved:
            #         self.LoadSprints()
            #     else:
            #         self.LoadSprints(self.selectedSprintIndex)

    def ClearStories(self):
        self.storyElements.clear()
        self.stories.clear()

        for i in range(len(self.storyBoardLayouts)):
            layout = self.storyBoardLayouts[i]
            while layout.count():
                widget = layout.takeAt(0).widget()
                if widget is not None:
                    widget.deleteLater()

    def LoadStories(self):
        response = requests.get('http://localhost:5165/GetSprintStories?sprintId=' + 
                                str(self.sprints[self.selectedSprintIndex]['id']), headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            self.ClearStories()
            
            self.stories = sorted(response.json(), key=lambda x: x['id'])

            for i in range(len(self.stories)):
                mode = 1
                if self.stories[i]['isAssigned']:
                    mode = 2
                elif self.stories[i]['developerName'] == None:
                    mode = 0

                self.storyElements.append(StoryElement(
                    i,
                    self.stories[i]['name'],
                    mode,
                    lambda story=self.stories[i], ia=self.stories[i]['isAssigned']: self.OpenStory(story, ia),
                    self.storyBoardWidgetContents[self.stories[i]['state']]
                ))
                self.storyElements[i].SetElement(self.storyBoardLayouts[self.stories[i]['state']])

            for i in range(len(self.storyBoardLayouts)):
                spacerItem = QtWidgets.QSpacerItem(20, 40, QtWidgets.QSizePolicy.Minimum, QtWidgets.QSizePolicy.Expanding)
                self.storyBoardLayouts[i].addItem(spacerItem)

    def OpenStory(self, story, isAssigned):
        self.storyWindow = StoryWindow(story, isAssigned, self.token)
        self.isReadyToClose = False
        self.storyWindow.exec_()

        # if self.storyWindow.isChanged:
        #     self.LoadStories()

    def EditProjectName(self):
        newProjectName, ok = QInputDialog.getText(
            self,
            'Изменение названия проекта',
            'Новое название',
            flags=QtCore.Qt.WindowCloseButtonHint
        )

        if ok:
            response = requests.put('http://localhost:5165/EditProjectName', headers={
                'Accept': 'application/json',
                "Authorization": "Bearer " + self.token
            }, json={
                "projectId": self.projectId,
                "name": newProjectName
            })

            if response.status_code == 200:
                #self.ui.projectLabel.setText(newProjectName)
                self.nameIsChanged = True

    def GetProjectChanges(self):
        request = QtNetwork.QNetworkRequest(QUrl('http://localhost:5165/GetProjectChanges?projectId='
                                                 + str(self.projectId)))
        
        request.setRawHeader(b'Accept', b'application/json')
        request.setRawHeader(b'Authorization', b'Bearer ' + self.token.encode('utf-8'))
        
        self.nam.get(request)

    def HandleProjectChangesReply(self, reply):
        content = json.loads(str(reply.readAll(), 'utf-8'))

        if self.lastChanges['name'] != content['name']:
            self.lastChanges['name'] = content['name']
            self.LoadProjectName()
        if self.lastChanges['members'] != content['members']:
            self.lastChanges['members'] = content['members']
            self.LoadDevelopers()
        if self.lastChanges['sprints'] != content['sprints']:
            self.lastChanges['sprints'] = content['sprints']
            self.LoadSprints(self.selectedSprintIndex, self.selectedSprintId)
        if self.lastChanges['boards'] != content['boards']:
            self.lastChanges['boards'] = content['boards']
            if self.selectedSprintIndex != -1:
                self.LoadStories()
        if self.lastChanges['backlog'] != content['backlog']:
            self.lastChanges['backlog'] = content['backlog']
        
        if not self.isClosed:
            QTimer.singleShot(1000, self.GetProjectChanges)