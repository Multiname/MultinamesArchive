from PyQt5 import QtWidgets, QtCore
from Widgets.AddStoryWidget import Ui_AddStoryWidget
from PyQt5.QtGui import QIcon

class AddStoryWindow(QtWidgets.QDialog):
    def __init__(self):
        super(AddStoryWindow, self).__init__()
        self.ui = Ui_AddStoryWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        self.setWindowIcon(QIcon('Resources/windows_icon.ico'))

        self.isCreated = False

        self.ui.createPushButton.clicked.connect(self.Confirm)

    def Confirm(self):
        self.isCreated = True
        self.name = self.ui.nameLineEdit.text()
        self.storyPoints = self.ui.storyPointsSpinBox.value()

        self.close()