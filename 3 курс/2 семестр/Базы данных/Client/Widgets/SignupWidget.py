# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'SignupWidget.ui'
#
# Created by: PyQt5 UI code generator 5.15.9
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_SignupWidget(object):
    def setupUi(self, SignupWidget):
        SignupWidget.setObjectName("SignupWidget")
        SignupWidget.resize(348, 263)
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(SignupWidget)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.nameLabel = QtWidgets.QLabel(SignupWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.nameLabel.setFont(font)
        self.nameLabel.setObjectName("nameLabel")
        self.verticalLayout_2.addWidget(self.nameLabel)
        self.nameLineEdit = QtWidgets.QLineEdit(SignupWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.nameLineEdit.setFont(font)
        self.nameLineEdit.setObjectName("nameLineEdit")
        self.verticalLayout_2.addWidget(self.nameLineEdit)
        self.loginLabel = QtWidgets.QLabel(SignupWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.loginLabel.setFont(font)
        self.loginLabel.setObjectName("loginLabel")
        self.verticalLayout_2.addWidget(self.loginLabel)
        self.loginLineEdit = QtWidgets.QLineEdit(SignupWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.loginLineEdit.setFont(font)
        self.loginLineEdit.setObjectName("loginLineEdit")
        self.verticalLayout_2.addWidget(self.loginLineEdit)
        self.passwordLabel = QtWidgets.QLabel(SignupWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.passwordLabel.setFont(font)
        self.passwordLabel.setObjectName("passwordLabel")
        self.verticalLayout_2.addWidget(self.passwordLabel)
        self.passwordLineEdit = QtWidgets.QLineEdit(SignupWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(12)
        self.passwordLineEdit.setFont(font)
        self.passwordLineEdit.setObjectName("passwordLineEdit")
        self.verticalLayout_2.addWidget(self.passwordLineEdit)
        self.signupPushButton = QtWidgets.QPushButton(SignupWidget)
        font = QtGui.QFont()
        font.setFamily("GOST type B")
        font.setPointSize(10)
        self.signupPushButton.setFont(font)
        self.signupPushButton.setObjectName("signupPushButton")
        self.verticalLayout_2.addWidget(self.signupPushButton)
        self.verticalLayout_2.setStretch(0, 1)
        self.verticalLayout_2.setStretch(1, 2)
        self.verticalLayout_2.setStretch(2, 1)
        self.verticalLayout_2.setStretch(3, 2)
        self.verticalLayout_2.setStretch(4, 1)
        self.verticalLayout_2.setStretch(5, 2)
        self.verticalLayout_2.setStretch(6, 1)

        self.retranslateUi(SignupWidget)
        QtCore.QMetaObject.connectSlotsByName(SignupWidget)

    def retranslateUi(self, SignupWidget):
        _translate = QtCore.QCoreApplication.translate
        SignupWidget.setWindowTitle(_translate("SignupWidget", "Регистрация"))
        self.nameLabel.setText(_translate("SignupWidget", "Имя"))
        self.loginLabel.setText(_translate("SignupWidget", "Логин"))
        self.passwordLabel.setText(_translate("SignupWidget", "Пароль"))
        self.signupPushButton.setText(_translate("SignupWidget", "Зарегистрироваться"))
