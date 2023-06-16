# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'AddStoryWidget.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_AddStoryWidget(object):
    def setupUi(self, AddStoryWidget):
        AddStoryWidget.setObjectName("AddStoryWidget")
        AddStoryWidget.resize(500, 150)
        AddStoryWidget.setMinimumSize(QtCore.QSize(500, 150))
        AddStoryWidget.setMaximumSize(QtCore.QSize(16777215, 150))
        self.AddStoryWidgetGridLayout = QtWidgets.QGridLayout(AddStoryWidget)
        self.AddStoryWidgetGridLayout.setObjectName("AddStoryWidgetGridLayout")
        self.nameLabel = QtWidgets.QLabel(AddStoryWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.nameLabel.setFont(font)
        self.nameLabel.setObjectName("nameLabel")
        self.AddStoryWidgetGridLayout.addWidget(self.nameLabel, 0, 0, 1, 1)
        self.createPushButton = QtWidgets.QPushButton(AddStoryWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(10)
        self.createPushButton.setFont(font)
        self.createPushButton.setObjectName("createPushButton")
        self.AddStoryWidgetGridLayout.addWidget(self.createPushButton, 2, 0, 1, 1)
        self.nameLineEdit = QtWidgets.QLineEdit(AddStoryWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.nameLineEdit.setFont(font)
        self.nameLineEdit.setObjectName("nameLineEdit")
        self.AddStoryWidgetGridLayout.addWidget(self.nameLineEdit, 0, 1, 1, 1)
        self.storyPointsSpinBox = QtWidgets.QSpinBox(AddStoryWidget)
        self.storyPointsSpinBox.setMaximumSize(QtCore.QSize(100, 16777215))
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.storyPointsSpinBox.setFont(font)
        self.storyPointsSpinBox.setMaximum(1000)
        self.storyPointsSpinBox.setSingleStep(10)
        self.storyPointsSpinBox.setObjectName("storyPointsSpinBox")
        self.AddStoryWidgetGridLayout.addWidget(self.storyPointsSpinBox, 1, 1, 1, 1)
        self.storyPointsLabel = QtWidgets.QLabel(AddStoryWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.storyPointsLabel.setFont(font)
        self.storyPointsLabel.setObjectName("storyPointsLabel")
        self.AddStoryWidgetGridLayout.addWidget(self.storyPointsLabel, 1, 0, 1, 1)

        self.retranslateUi(AddStoryWidget)
        QtCore.QMetaObject.connectSlotsByName(AddStoryWidget)

    def retranslateUi(self, AddStoryWidget):
        _translate = QtCore.QCoreApplication.translate
        AddStoryWidget.setWindowTitle(_translate("AddStoryWidget", "Новый стори"))
        self.nameLabel.setText(_translate("AddStoryWidget", "Название"))
        self.createPushButton.setText(_translate("AddStoryWidget", "Создать"))
        self.storyPointsLabel.setText(_translate("AddStoryWidget", "Story points"))
