from PyQt5 import QtWidgets, QtCore, QtGui
from PyQt5.QtCore import QObject, QEvent
from PyQt5.QtWidgets import QTableWidgetItem, QPushButton, QHeaderView, \
    QComboBox, QCheckBox, QWidget, QHBoxLayout, QInputDialog
from Widgets.BacklogWidget import Ui_BacklogWidget
from Windows.AddEpicWindow import AddEpicWindow
from Windows.AddStoryWindow import AddStoryWindow
from Windows.AddTaskWindow import AddTaskWindow
import requests
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import QTimer

class BacklogWindow(QtWidgets.QDialog):
    def __init__(self, projectWindow, token, projectId, members, isOwner):
        super(BacklogWindow, self).__init__()
        self.ui = Ui_BacklogWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.priorities = [
            'Незначительный',
            'Низкий',
            'Средний',
            'Высокий',
            'Экстренный'
        ]

        self.ui.epicsTableWidget.verticalHeader().setVisible(False)
        self.ui.storiesTableWidget.verticalHeader().setVisible(False)
        self.ui.tasksTableWidget.verticalHeader().setVisible(False)

        self.ui.epicsTableWidget.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        self.ui.storiesTableWidget.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        self.ui.tasksTableWidget.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)

        self.ui.epicsTableWidget.viewport().installEventFilter(self)
        self.ui.storiesTableWidget.viewport().installEventFilter(self)
        self.ui.tasksTableWidget.viewport().installEventFilter(self)

        self.projectWindow = projectWindow
        self.token = token
        self.projectId = projectId
        self.members = members
        self.isOwner = isOwner

        self.isClosed = False

        self.epics = []
        self.stories = []
        self.tasks = []

        self.selectedEpicId = None
        self.selectedStoryId = None

        self.LoadEpics()

        self.lastChanges = self.projectWindow.lastChanges['backlog']
        QTimer.singleShot(1000, self.CheckChanges)

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        self.isClosed = True
        return super().closeEvent(a0)





    def ClearEpics(self):
        self.ui.epicsTableWidget.clear()
        self.ui.epicsTableWidget.setColumnCount(0)
        self.epics.clear()

    def ClearStories(self):
        self.ui.storiesTableWidget.clear()
        self.ui.storiesTableWidget.setColumnCount(0)
        self.stories.clear()

    def ClearTasks(self):
        self.ui.tasksTableWidget.clear()
        self.ui.tasksTableWidget.setColumnCount(0)
        self.tasks.clear()





    def LoadEpics(self):
        self.ClearEpics()

        response = requests.get('http://localhost:5165/GetEpics?projectId=' + str(self.projectId), headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            self.epics = sorted(response.json(), key=lambda x: x['id'])

        header = self.ui.epicsTableWidget.horizontalHeader()
        if self.isOwner:
            self.ui.epicsTableWidget.setColumnCount(4)
            self.ui.epicsTableWidget.setHorizontalHeaderLabels(
                ("Название", "Приоритет", "Готово", "")
            )
            
            header.setSectionResizeMode(3, QHeaderView.ResizeToContents)
        else:
            self.ui.epicsTableWidget.setColumnCount(3)
            self.ui.epicsTableWidget.setHorizontalHeaderLabels(
                ("Название", "Приоритет", "Готово")
            )

        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)

        epicsNumber = len(self.epics)
        if self.isOwner:
            self.ui.epicsTableWidget.setRowCount(epicsNumber + 1)
        else:
            self.ui.epicsTableWidget.setRowCount(epicsNumber)

        for i in range(epicsNumber):
            item = QTableWidgetItem(str(self.epics[i]['name']))
            self.ui.epicsTableWidget.setItem(i, 0, item)

            if self.isOwner:
                item = QComboBox(self)
                item.setObjectName("EpicComboBox_" + str(self.epics[i]['id']))
                item.addItems(self.priorities)
                item.setCurrentIndex(self.epics[i]['priority'])
                item.activated[int].connect(lambda index, id=self.epics[i]['id']: self.EditPriority(index, id))
                self.ui.epicsTableWidget.setCellWidget(i, 1, item)

                checkBox = QCheckBox(self)
                checkBox.setObjectName("EpicCheckBox_" + str(self.epics[i]['id']))
                checkBox.setChecked(self.epics[i]['isDone'])
                checkBox.clicked.connect(lambda _, cb=checkBox, id=self.epics[i]['id']: self.EditEpicIsDone(cb, id))

                item = QWidget()
                layout = QHBoxLayout(item)
                layout.addWidget(checkBox)
                layout.setAlignment(QtCore.Qt.AlignCenter)
                layout.setContentsMargins(0,0,0,0)
                item.setLayout(layout)

                self.ui.epicsTableWidget.setCellWidget(i, 2, item)

                item = QPushButton()
                item.setMinimumSize(QtCore.QSize(40, 37))
                item.setMaximumSize(QtCore.QSize(40, 37))
                item.setObjectName("removeEpicPushButton_" + str(self.epics[i]['id']))
                item.setText("X")
                item.clicked.connect(lambda _, id=self.epics[i]['id']: self.RemoveEpic(id))
                self.ui.epicsTableWidget.setCellWidget(i, 3, item)
            else:
                item = QTableWidgetItem(self.priorities[self.epics[i]['priority']])
                self.ui.epicsTableWidget.setItem(i, 1, item)

                item = QTableWidgetItem('✓' if self.epics[i]['isDone'] else '')
                self.ui.epicsTableWidget.setItem(i, 2, item)

        if self.isOwner:
            item = QPushButton(self)
            item.setObjectName("AddEpicButton")
            item.setText("Добавить")
            item.clicked.connect(self.AddEpic)
            self.ui.epicsTableWidget.setCellWidget(epicsNumber, 0, item)



    def LoadStories(self):
        self.ClearStories()

        if self.selectedEpicId == None:
            return
        
        response = requests.get('http://localhost:5165/GetStories?epicId=' + str(self.selectedEpicId), headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            self.stories = sorted(response.json(), key=lambda x: x['id'])
        else:
            self.selectedEpicId = None
            return

        header = self.ui.storiesTableWidget.horizontalHeader()
        if self.isOwner:
            self.ui.storiesTableWidget.setColumnCount(4)
            self.ui.storiesTableWidget.setHorizontalHeaderLabels(
                ("Название", "Разработчик", "SP", "")
            )

            header.setSectionResizeMode(3, QHeaderView.ResizeToContents)
        else:
            self.ui.storiesTableWidget.setColumnCount(3)
            self.ui.storiesTableWidget.setHorizontalHeaderLabels(
                ("Название", "Разработчик", "SP")
            )
            
        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)

        storiesNumber = len(self.stories)
        if self.isOwner:
            self.ui.storiesTableWidget.setRowCount(storiesNumber + 1)
        else:
            self.ui.storiesTableWidget.setRowCount(storiesNumber)

        for i in range(storiesNumber):
            item = QTableWidgetItem(str(self.stories[i]['name']))
            self.ui.storiesTableWidget.setItem(i, 0, item)

            item = QTableWidgetItem(str(self.stories[i]['storyPoints']))
            self.ui.storiesTableWidget.setItem(i, 2, item)

            if self.isOwner:
                item = QComboBox(self)
                item.setObjectName("StoryComboBox_" + str(self.stories[i]['id']))
                item.addItems(list(map(lambda x: x['name'], self.members)))
                item.addItem('Не выбран')

                developerSearch = list(filter(lambda x: x['id'] == self.stories[i]['developerId'], self.members))
                index = len(self.members)
                if len(developerSearch) != 0:
                    index = self.members.index(developerSearch[0])
                item.setCurrentIndex(index)

                item.activated[int].connect(lambda index, id=self.stories[i]['id']: self.EditStoryDeveloper(index, id))
                self.ui.storiesTableWidget.setCellWidget(i, 1, item)

                item = QPushButton()
                item.setMinimumSize(QtCore.QSize(40, 37))
                item.setMaximumSize(QtCore.QSize(40, 37))
                item.setObjectName("removeStoryPushButton_" + str(self.stories[i]['id']))
                item.setText("X")
                item.clicked.connect(lambda _, id=self.stories[i]['id']: self.RemoveStory(id))
                self.ui.storiesTableWidget.setCellWidget(i, 3, item)
            else:
                developers = list(map(lambda x: x['name'], self.members))
                developerSearch = list(filter(lambda x: x['id'] == self.stories[i]['developerId'], self.members))
                
                value = 'Не выбран'
                index = len(self.members)
                if len(developerSearch) != 0:
                    index = self.members.index(developerSearch[0])
                    value = developers[index]

                item = QTableWidgetItem(value)
                self.ui.storiesTableWidget.setItem(i, 1, item)

        if self.isOwner:
            item = QPushButton(self)
            item.setObjectName("AddStoryButton")
            item.setText("Добавить")
            item.clicked.connect(self.AddStory)
            self.ui.storiesTableWidget.setCellWidget(storiesNumber, 0, item)



    def LoadTasks(self):
        self.ClearTasks()

        if self.selectedStoryId == None:
            return

        response = requests.get('http://localhost:5165/GetTasks?storyId=' + str(self.selectedStoryId), headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        })

        if response.status_code == 200:
            self.tasks = sorted(response.json(), key=lambda x: x['id'])
        else:
            self.selectedStoryId = None
            return

        header = self.ui.tasksTableWidget.horizontalHeader()
        if self.isOwner:
            self.ui.tasksTableWidget.setColumnCount(4)
            self.ui.tasksTableWidget.setHorizontalHeaderLabels(
                ("Название", "Часы", "Готово", "")
            )

            header.setSectionResizeMode(3, QHeaderView.ResizeToContents)
        else:
            self.ui.tasksTableWidget.setColumnCount(3)
            self.ui.tasksTableWidget.setHorizontalHeaderLabels(
                ("Название", "Часы", "Готово")
            )

        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)

        tasksNumber = len(self.tasks)
        if self.isOwner:
            self.ui.tasksTableWidget.setRowCount(tasksNumber + 1)
        else:
            self.ui.tasksTableWidget.setRowCount(tasksNumber)

        for i in range(tasksNumber):
            item = QTableWidgetItem(str(self.tasks[i]['name']))
            self.ui.tasksTableWidget.setItem(i, 0, item)

            item = QTableWidgetItem(str(self.tasks[i]['estimatedHours']))
            self.ui.tasksTableWidget.setItem(i, 1, item)

            if self.isOwner:
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

                item = QPushButton()
                item.setMinimumSize(QtCore.QSize(40, 37))
                item.setMaximumSize(QtCore.QSize(40, 37))
                item.setObjectName("removeTaskPushButton_" + str(self.tasks[i]['id']))
                item.setText("X")
                item.clicked.connect(lambda _, id=self.tasks[i]['id']: self.RemoveTask(id))
                self.ui.tasksTableWidget.setCellWidget(i, 3, item)
            else:
                item = QTableWidgetItem('✓' if self.tasks[i]['isDone'] else '')
                self.ui.tasksTableWidget.setItem(i, 2, item)

        if self.isOwner:
            item = QPushButton(self)
            item.setObjectName("AddTaskButton")
            item.setText("Добавить")
            item.clicked.connect(self.AddTask)
            self.ui.tasksTableWidget.setCellWidget(tasksNumber, 0, item)





    def eventFilter(self, source: QObject, event: QEvent) -> bool:
        if self.isOwner and \
                event.type() == QtCore.QEvent.MouseButtonDblClick and \
                event.buttons() == QtCore.Qt.LeftButton:
            if source is self.ui.epicsTableWidget.viewport():
                item = self.ui.epicsTableWidget.itemAt(event.pos())
                if item is not None:
                    self.EditEpicName(item)
            elif source is self.ui.storiesTableWidget.viewport():
                item = self.ui.storiesTableWidget.itemAt(event.pos())
                if item is not None:
                    self.EditStory(item)
            elif source is self.ui.tasksTableWidget.viewport():
                item = self.ui.tasksTableWidget.itemAt(event.pos())
                if item is not None:
                    self.EditTask(item)

        if event.type() == QtCore.QEvent.MouseButtonPress and \
                    event.buttons() == QtCore.Qt.LeftButton:
                if source is self.ui.epicsTableWidget.viewport():
                    item = self.ui.epicsTableWidget.itemAt(event.pos())
                    if item is not None:
                        if self.selectedEpicId != self.epics[item.row()]['id']:
                            self.selectedStoryId = None
                            self.LoadTasks()

                        self.selectedEpicId = self.epics[item.row()]['id']
                        self.LoadStories()
                elif source is self.ui.storiesTableWidget.viewport():
                    item = self.ui.storiesTableWidget.itemAt(event.pos())
                    if item is not None:
                        self.selectedStoryId = self.stories[item.row()]['id']
                        self.LoadTasks()

        return super().eventFilter(source, event)



    def EditEpicName(self, item):
        newEpicName, ok = QInputDialog.getText(
            self,
            'Изменение названия эпика',
            'Новое название',
            flags=QtCore.Qt.WindowCloseButtonHint
        )

        if ok:
            response = requests.put('http://localhost:5165/EditEpicName', headers={
                'Accept': 'application/json',
                "Authorization": "Bearer " + self.token
            }, json={
                "epicId": self.epics[item.row()]['id'],
                "name": newEpicName
            })

            if response.status_code == 200:
                self.LoadEpics()

    def EditPriority(self, index, epicId):
        response = requests.put('http://localhost:5165/EditEpicPriority', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "epicId": epicId,
            "priority": index
        })

        if response.status_code == 200:
            self.LoadEpics()

    def EditEpicIsDone(self, checkBox, epicId):
        response = requests.put('http://localhost:5165/EditEpicIsDone', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "epicId": epicId,
            "isDone": checkBox.isChecked()
        })

        if response.status_code == 200:
            self.LoadEpics()



    def EditStory(self, item):
        if item.column() == 0:
            newStoryName, ok = QInputDialog.getText(
                self,
                'Изменение названия стори',
                'Новое название',
                flags=QtCore.Qt.WindowCloseButtonHint
            )

            if ok:
                response = requests.put('http://localhost:5165/EditStoryName', headers={
                    'Accept': 'application/json',
                    "Authorization": "Bearer " + self.token
                }, json={
                    "storyId": self.stories[item.row()]['id'],
                    "name": newStoryName
                })

                if response.status_code == 200:
                    self.LoadStories()
        elif item.column() == 2:
            newStoryPoints, ok = QInputDialog.getText(
                self,
                'Изменение числа story points',
                'Story points',
                flags=QtCore.Qt.WindowCloseButtonHint
            )

            if ok:
                response = requests.put('http://localhost:5165/EditStoryPoints', headers={
                    'Accept': 'application/json',
                    "Authorization": "Bearer " + self.token
                }, json={
                    "storyId": self.stories[item.row()]['id'],
                    "storyPoints": newStoryPoints
                })

                if response.status_code == 200:
                    self.LoadStories()

    def EditStoryDeveloper(self, index, storyId):
        if index >= len(self.members):
            developerId = -1
        else:
            developerId = self.members[index]['id']

        response = requests.put('http://localhost:5165/EditStoryDeveloper', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "storyId": storyId,
            "developerId": developerId
        })

        if response.status_code == 200:
            self.LoadStories()



    def EditTask(self, item):
        if item.column() == 0:
            newTaskName, ok = QInputDialog.getText(
                self,
                'Изменение названия таска',
                'Новое название',
                flags=QtCore.Qt.WindowCloseButtonHint
            )

            if ok:
                response = requests.put('http://localhost:5165/EditTaskName', headers={
                    'Accept': 'application/json',
                    "Authorization": "Bearer " + self.token
                }, json={
                    "taskId": self.tasks[item.row()]['id'],
                    "name": newTaskName
                })

                if response.status_code == 200:
                    self.LoadTasks()
        elif item.column() == 1:
            newTaskEstimatedHours, ok = QInputDialog.getText(
                self,
                'Изменение примерного времени',
                'Примерное кол-во часов на решение',
                flags=QtCore.Qt.WindowCloseButtonHint
            )

            if ok:
                response = requests.put('http://localhost:5165/EditTaskEstimatedHours', headers={
                    'Accept': 'application/json',
                    "Authorization": "Bearer " + self.token
                }, json={
                    "taskId": self.tasks[item.row()]['id'],
                    "estimatedHours": newTaskEstimatedHours
                })

                if response.status_code == 200:
                    self.LoadTasks()

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





    def AddEpic(self):
        self.addEpicWindow = AddEpicWindow()
        self.addEpicWindow.exec_()

        if self.addEpicWindow.isCreated:
            response = requests.post('http://localhost:5165/AddEpic', headers={
                'Accept': 'application/json',
                "Authorization": "Bearer " + self.token
            }, json={
                "name": self.addEpicWindow.name,
                "projectId": self.projectId,
                "priority": self.addEpicWindow.priority
            })

            if response.status_code == 200:
                self.LoadEpics()

    def AddStory(self):
        self.addStoryWindow = AddStoryWindow()
        self.addStoryWindow.exec_()

        if self.addStoryWindow.isCreated:
            response = requests.post('http://localhost:5165/AddStory', headers={
                'Accept': 'application/json',
                "Authorization": "Bearer " + self.token
            }, json={
                "name": self.addStoryWindow.name,
                "epicId": self.selectedEpicId,
                "storyPoints": self.addStoryWindow.storyPoints
            })

            if response.status_code == 200:
                self.LoadStories()

    def AddTask(self):
        self.addTaskWindow = AddTaskWindow()
        self.addTaskWindow.exec_()

        if self.addTaskWindow.isCreated:
            response = requests.post('http://localhost:5165/AddTask', headers={
                'Accept': 'application/json',
                "Authorization": "Bearer " + self.token
            }, json={
                "name": self.addTaskWindow.name,
                "storyId": self.selectedStoryId,
                "estimatedHours": self.addTaskWindow.estimatedHours
            })

            if response.status_code == 200:
                self.LoadTasks()
    




    def RemoveEpic(self, epicId):
        response = requests.post('http://localhost:5165/RemoveEpic', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "epicId": epicId
        })

        if response.status_code == 200:
            if self.selectedEpicId == epicId:
                self.selectedEpicId = None
                self.selectedStoryId = None
                self.LoadStories()
                self.LoadTasks()
            self.LoadEpics()
    
    def RemoveStory(self, storyId):
        response = requests.post('http://localhost:5165/RemoveStory', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "storyId": storyId
        })

        if response.status_code == 200:
            if self.selectedStoryId == storyId:
                self.selectedStoryId = None
                self.LoadTasks()
            self.LoadStories()

    def RemoveTask(self, taskId):
        response = requests.post('http://localhost:5165/RemoveTask', headers={
            'Accept': 'application/json',
            "Authorization": "Bearer " + self.token
        }, json={
            "taskId": taskId
        })

        if response.status_code == 200:
            self.LoadTasks()

    def CheckChanges(self):
        changes = self.projectWindow.lastChanges['backlog']

        if self.lastChanges != changes:
            self.LoadEpics()
            self.LoadStories()
            self.LoadTasks()

        self.lastChanges = changes

        if not self.isClosed:
            QTimer.singleShot(1000, self.CheckChanges)