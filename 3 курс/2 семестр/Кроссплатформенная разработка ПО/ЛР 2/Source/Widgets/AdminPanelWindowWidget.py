from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_AdminPanelWindowWidget(object):
    def setupUi(self, AdminPanelWindowWidget):
        AdminPanelWindowWidget.setObjectName("AdminPanelWindowWidget")
        AdminPanelWindowWidget.resize(650, 484)
        self.clientsTableWidget = QtWidgets.QTableWidget(AdminPanelWindowWidget)
        self.clientsTableWidget.setGeometry(QtCore.QRect(20, 20, 611, 192))
        self.clientsTableWidget.setObjectName("clientsTableWidget")
        self.clientsTableWidget.setColumnCount(0)
        self.clientsTableWidget.setRowCount(0)
        self.clientsTableWidget.verticalHeader().setVisible(False)
        self.contractsTableWidget = QtWidgets.QTableWidget(AdminPanelWindowWidget)
        self.contractsTableWidget.setGeometry(QtCore.QRect(20, 230, 611, 192))
        self.contractsTableWidget.setObjectName("contractsTableWidget")
        self.contractsTableWidget.setColumnCount(0)
        self.contractsTableWidget.setRowCount(0)
        self.contractsTableWidget.verticalHeader().setVisible(False)
        self.exitPushButton = QtWidgets.QPushButton(AdminPanelWindowWidget)
        self.exitPushButton.setGeometry(QtCore.QRect(510, 430, 121, 41))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.exitPushButton.setFont(font)
        self.exitPushButton.setObjectName("exitPushButton")

        self.retranslateUi(AdminPanelWindowWidget)
        QtCore.QMetaObject.connectSlotsByName(AdminPanelWindowWidget)

    def retranslateUi(self, AdminPanelWindowWidget):
        _translate = QtCore.QCoreApplication.translate
        AdminPanelWindowWidget.setWindowTitle(_translate("AdminPanelWindowWidget", "Панель админа"))
        self.exitPushButton.setText(_translate("AdminPanelWindowWidget", "Выйти"))
