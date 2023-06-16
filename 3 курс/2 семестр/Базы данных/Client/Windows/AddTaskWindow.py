from PyQt5 import QtWidgets, QtCore
from Widgets.AddTaskWidget import Ui_AddTaskWidget
from PyQt5.QtGui import QIcon

class AddTaskWindow(QtWidgets.QDialog):
    def __init__(self):
        super(AddTaskWindow, self).__init__()
        self.ui = Ui_AddTaskWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.isCreated = False

        self.ui.createPushButton.clicked.connect(self.Confirm)

    def Confirm(self):
        self.isCreated = True
        self.name = self.ui.nameLineEdit.text()
        self.estimatedHours = self.ui.estimatedHoursSpinBox.value()

        self.close()