from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import pyqtSignal

class ClickableLabel(QtWidgets.QLabel):
    clicked = pyqtSignal()

    def mouseReleaseEvent(self, e):
        super().mouseReleaseEvent(e)

        self.clicked.emit()

class StoryElement:
    def __init__(self, index, name, mode, clickedLambda, scrollAreaWidgetContents):
        index = str(index)

        self.storyLabel = ClickableLabel(scrollAreaWidgetContents)
        self.storyLabel.setMinimumSize(QtCore.QSize(0, 40))
        self.storyLabel.setMaximumSize(QtCore.QSize(16777215, 16777215))
        font = QtGui.QFont()
        font.setPointSize(12)

        if mode == 0:
            font.setItalic(True)
        elif mode == 2:
            font.setBold(True)

        self.storyLabel.setFont(font)
        self.storyLabel.setFrameShape(QtWidgets.QFrame.WinPanel)
        self.storyLabel.setFrameShadow(QtWidgets.QFrame.Raised)
        self.storyLabel.setWordWrap(True)
        self.storyLabel.setObjectName("storyLabel_" + str(index))

        _translate = QtCore.QCoreApplication.translate
        self.storyLabel.setText(_translate("ProjectWidget", name))

        self.storyLabel.clicked.connect(clickedLambda)

    def SetElement(self, verticalLayout):
        verticalLayout.addWidget(self.storyLabel)