from PyQt5 import QtCore, QtGui, QtWidgets

class MemberElement:
    def __init__(self, index, developerName, isOwner, scrollAreaWidgetContents, removeLambda=None):
        index = str(index)

        self.developerFrame = QtWidgets.QFrame(scrollAreaWidgetContents)
        self.developerFrame.setFrameShape(QtWidgets.QFrame.Box)
        self.developerFrame.setFrameShadow(QtWidgets.QFrame.Raised)
        self.developerFrame.setObjectName("developerFrame_" + index)
        self.developerFrameHorizontalLayout = QtWidgets.QHBoxLayout(self.developerFrame)
        self.developerFrameHorizontalLayout.setObjectName("developerFrameHorizontalLayout_" + index)

        self.developerLabel = QtWidgets.QLabel(self.developerFrame)
        self.developerLabel.setObjectName("developerLabel_" + index)
        self.developerFrameHorizontalLayout.addWidget(self.developerLabel)
        
        if isOwner:
            font = QtGui.QFont()
            font.setBold(True)
            font.setWeight(75)
            self.developerLabel.setFont(font)

        _translate = QtCore.QCoreApplication.translate
        self.developerLabel.setText(_translate("ProjectWidget", developerName))

        if removeLambda != None:
            if not isOwner:
                self.removeDeveloperPushButton = QtWidgets.QPushButton(self.developerFrame)
                self.removeDeveloperPushButton.setMinimumSize(QtCore.QSize(25, 25))
                self.removeDeveloperPushButton.setMaximumSize(QtCore.QSize(25, 25))
                self.removeDeveloperPushButton.setObjectName("removeDeveloperPushButton_" + index)
                self.developerFrameHorizontalLayout.addWidget(self.removeDeveloperPushButton)
                self.removeDeveloperPushButton.setText(_translate("ProjectWidget", "X"))
                self.removeDeveloperPushButton.clicked.connect(removeLambda)

    def SetElement(self, verticalLayout):
        verticalLayout.addWidget(self.developerFrame)