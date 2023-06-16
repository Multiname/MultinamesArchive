from PyQt5 import QtWidgets, QtCore, QtGui
from Widgets.EditSprintWidget import Ui_EditSprintWidget
from PyQt5.QtWidgets import QTableWidgetItem, QHeaderView, QWidget, QHBoxLayout, QCheckBox, QInputDialog
import requests
from PyQt5.QtGui import QIcon

class EditSprintWindow(QtWidgets.QDialog):
    def __init__(self, projectId, sprint, token):
        super(EditSprintWindow, self).__init__()
        self.ui = Ui_EditSprintWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.projectId = projectId
        self.sprint = sprint
        self.token = token

        self.newStartDate = None
        self.newEndDate = None
        self.isChanged = False
        self.isRemoved = False

        self.epics = []
        self.priorities = [
            'Незначительный',
            'Низкий',
            'Средний',
            'Высокий',
            'Экстренный'
        ]

        self.ui.epicsAndStoriesTableWidget.verticalHeader().setVisible(False)
        self.ui.epicsAndStoriesTableWidget.horizontalHeader().setVisible(False)
        self.ui.epicsAndStoriesTableWidget.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)

        self.ui.nameLabel.setText(sprint['name'])
        self.ui.startDateEdit.setDate(QtCore.QDate.fromString(sprint['startDate'], 'dd.MM.yyyy'))
        self.ui.endDateEdit.setDate(QtCore.QDate.fromString(sprint['endDate'], 'dd.MM.yyyy'))

        self.ui.removePushButton.clicked.connect(self.RemoveSprint)

        self.LoadEpicsAndStories()

        self.ui.renamePushButton.clicked.connect(self.EditSprintName)
        self.ui.startDateEdit.dateChanged.connect(lambda x: self.HandleDateChange(x, True))
        self.ui.endDateEdit.dateChanged.connect(lambda x: self.HandleDateChange(x, False))

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        if not self.isRemoved:
            if self.newStartDate != None:
                self.EditDate(True)
            if self.newEndDate != None:
                self.EditDate(False)

        return super().closeEvent(a0)

    def ClearEpicsAndStories(self):
        self.epics.clear()
        self.ui.epicsAndStoriesTableWidget.setColumnCount(0)
        self.ui.epicsAndStoriesTableWidget.clear()

    def LoadEpicsAndStories(self):
        self.ClearEpicsAndStories()

        response = requests.get('http://localhost:5165/GetStoriesAndEpics?projectId=' + str(self.projectId) + 
                                "&sprintId=" + str(self.sprint['id']), 
                        headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            self.epics = sorted(sorted(sorted(response.json(),
                                              key=lambda x: x['id']),
                                              key=lambda x: x['priority'], reverse=True),
                                              key=lambda x: x['isDone'])

        header = self.ui.epicsAndStoriesTableWidget.horizontalHeader()
        self.ui.epicsAndStoriesTableWidget.setColumnCount(3)
        
        header.setSectionResizeMode(0, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(1, QHeaderView.Stretch)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)

        rowNumber = len(self.epics)
        for epic in self.epics:
            rowNumber += len(epic['stories'])
        self.ui.epicsAndStoriesTableWidget.setRowCount(rowNumber)

        currentRow = 0
        font = QtGui.QFont()
        font.setBold(True)
        for i in range(len(self.epics)):
            item = QTableWidgetItem(str(self.epics[i]['name']))
            item.setFont(font)
            self.ui.epicsAndStoriesTableWidget.setItem(currentRow, 0, item)

            item = QTableWidgetItem(self.priorities[self.epics[i]['priority']])
            item.setFont(font)
            self.ui.epicsAndStoriesTableWidget.setItem(currentRow, 1, item)

            item = QTableWidgetItem('Завершено' if self.epics[i]['isDone'] else 'Выполняется')
            item.setFont(font)
            self.ui.epicsAndStoriesTableWidget.setItem(currentRow, 2, item)

            currentRow += 1

            for j in range(len(self.epics[i]['stories'])):
                checkBox = QCheckBox(self)
                checkBox.setObjectName("StoryCheckBox_" + str(self.epics[i]['stories'][j]['id']))
                checkBox.setChecked(self.epics[i]['stories'][j]['isPicked'])
                checkBox.clicked.connect(lambda _, cb=checkBox, id=self.epics[i]['stories'][j]['id']: self.EditIsPicked(cb, id))

                item = QWidget()
                layout = QHBoxLayout(item)

                spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
                layout.addItem(spacerItem)

                layout.addWidget(checkBox)
                layout.setAlignment(QtCore.Qt.AlignCenter)
                layout.setContentsMargins(0,0,5,0)
                item.setLayout(layout)

                self.ui.epicsAndStoriesTableWidget.setCellWidget(currentRow, 0, item)
                
                item = QTableWidgetItem(str(self.epics[i]['stories'][j]['name']))
                self.ui.epicsAndStoriesTableWidget.setItem(currentRow, 1, item)

                item = QTableWidgetItem(str(self.epics[i]['stories'][j]['storyPoints']) + ' sp')
                self.ui.epicsAndStoriesTableWidget.setItem(currentRow, 2, item)

                currentRow += 1
    
    def EditSprintName(self):
        newSprintName, ok = QInputDialog.getText(
            self,
            'Изменение имени спринта',
            'Новое имя',
            flags=QtCore.Qt.WindowCloseButtonHint
        )

        if ok:
            response = requests.put('http://localhost:5165/EditSprintName', headers={
                'Accept': 'application/json',
                "Authorization": "Bearer " + self.token
            }, json={
                "id": self.sprint['id'],
                "name": newSprintName
            })

            if response.status_code == 200:
                self.isChanged = True
                self.ui.nameLabel.setText(newSprintName)

    def HandleDateChange(self, date, isStart):
        if isStart:
            self.newStartDate = date.toString('dd.MM.yyyy')
        else:
            self.newEndDate = date.toString('dd.MM.yyyy')
        self.isChanged = True

    def EditDate(self, isStart):
        response = requests.put('http://localhost:5165/EditSprintDate', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "id": self.sprint['id'],
            "date": self.newStartDate if isStart else self.newEndDate,
            "isStart": isStart
        })

        if response.status_code == 200:
            self.isChanged = True

    def EditIsPicked(self, checkBox, id):
        response = requests.put('http://localhost:5165/EditStoryIsPicked', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "isPicked": checkBox.isChecked(),
            "sprintId": self.sprint['id'],
            "storyId": id
        })

        if response.status_code == 200:
            self.isChanged = True
            self.LoadEpicsAndStories()

    def RemoveSprint(self):
        response = requests.post('http://localhost:5165/RemoveSprint', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "sprintId": self.sprint['id']
        })

        if response.status_code == 200:
            self.isChanged = True
            self.isRemoved = True
            self.close()