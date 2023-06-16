from PyQt5 import QtWidgets, QtCore
from Widgets.AddEpicWidget import Ui_AddEpicWidget
from PyQt5.QtGui import QIcon

class AddEpicWindow(QtWidgets.QDialog):
    def __init__(self):
        super(AddEpicWindow, self).__init__()
        self.ui = Ui_AddEpicWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.ui.priorityComboBox.addItems([
            'Незначительный',
            'Низкий',
            'Средний',
            'Высокий',
            'Экстренный'
        ])
        self.ui.createPushButton.clicked.connect(self.Confirm)

        self.isCreated = False

    def Confirm(self):
        self.isCreated = True
        self.name = self.ui.nameLineEdit.text()
        self.priority = self.ui.priorityComboBox.currentIndex()

        self.close()