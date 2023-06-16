from PyQt5 import QtWidgets, QtCore
from Widgets.StoryWidget import Ui_StoryWidget
from PyQt5.QtWidgets import QTableWidgetItem, QHBoxLayout, QHeaderView, QWidget, QCheckBox
import requests
from PyQt5.QtGui import QIcon

class StoryWindow(QtWidgets.QDialog):
    def __init__(self, story, isAssigned, token):
        super(StoryWindow, self).__init__()
        self.ui = Ui_StoryWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.story = story
        self.isAssigned = isAssigned
        self.token = token

        self.tasks = []
        self.isChanged = False

        self.ui.tasksTableWidget.verticalHeader().setVisible(False)

        self.ui.nameLabel.setText(story['name'])
        self.ui.epicLabel.setText(story['epicName'])
        self.ui.developerLabel.setText(story['developerName'] if story['developerName'] != None else 'Не назначен')
        self.ui.storyPointsLabel.setText(str(story['storyPoints']))

        self.ui.stateComboBox.addItems([
            'На выполнение',
            'Отклонено',
            'Выполняется',
            'Готово к проверке',
            'Сделано'
        ])
        self.ui.stateComboBox.setCurrentIndex(story['state'])
        self.ui.stateComboBox.activated[int].connect(self.EditStoryState)

        self.LoadTasks()

    def EditStoryState(self, state):
        response = requests.put('http://localhost:5165/EditStoryState', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "storyId": self.story['id'],
            "state": state
        })

        if response.status_code == 200:
            self.isChanged = True

    def ClearTasks(self):
        self.ui.tasksTableWidget.clear()
        self.ui.tasksTableWidget.setColumnCount(0)
        self.tasks.clear()

    def LoadTasks(self):
        self.ClearTasks()

        response = requests.get('http://localhost:5165/GetTasks?storyId=' + str(self.story['id']), headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            self.tasks = sorted(response.json(), key=lambda x: x['id'])

        header = self.ui.tasksTableWidget.horizontalHeader()
        self.ui.tasksTableWidget.setColumnCount(3)
        self.ui.tasksTableWidget.setHorizontalHeaderLabels(
            ("Таск", "Часы", "Готово")
        )
        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)

        tasksNumber = len(self.tasks)
        self.ui.tasksTableWidget.setRowCount(tasksNumber)

        for i in range(tasksNumber):
            item = QTableWidgetItem(str(self.tasks[i]['name']))
            self.ui.tasksTableWidget.setItem(i, 0, item)

            item = QTableWidgetItem(str(self.tasks[i]['estimatedHours']))
            self.ui.tasksTableWidget.setItem(i, 1, item)

            if self.isAssigned:
                checkBox = QCheckBox(self)
                checkBox.setObjectName("TaskCheckBox_" + str(self.tasks[i]['id']))
                checkBox.setChecked(self.tasks[i]['isDone'])
                checkBox.clicked.connect(lambda _, cb=checkBox, id=self.tasks[i]['id']: self.EditTaskIsDone(cb, id))

                item = QWidget()
                layout = QHBoxLayout(item)
                layout.addWidget(checkBox)
                layout.setAlignment(QtCore.Qt.AlignCenter)
                layout.setContentsMargins(0,0,0,0)
                item.setLayout(layout)

                self.ui.tasksTableWidget.setCellWidget(i, 2, item)
            else:
                item = QTableWidgetItem('✓' if self.tasks[i]['isDone'] else '')
                self.ui.tasksTableWidget.setItem(i, 2, item)

    def EditTaskIsDone(self, checkBox, taskId):
        response = requests.put('http://localhost:5165/EditTaskIsDone', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "taskId": taskId,
            "isDone": checkBox.isChecked()
        })

        if response.status_code == 200:
            self.LoadTasks()