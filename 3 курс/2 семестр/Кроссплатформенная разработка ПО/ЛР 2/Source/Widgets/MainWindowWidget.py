from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindowWidget(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(799, 556)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.productsTableWidget = QtWidgets.QTableWidget(self.centralwidget)
        self.productsTableWidget.setGeometry(QtCore.QRect(20, 70, 751, 461))
        self.productsTableWidget.setObjectName("productsTableWidget")
        self.productsTableWidget.setColumnCount(0)
        self.productsTableWidget.setRowCount(0)
        self.productsTableWidget.verticalHeader().setVisible(False)
        self.userLabel = QtWidgets.QLabel(self.centralwidget)
        self.userLabel.setGeometry(QtCore.QRect(20, 20, 601, 31))
        font = QtGui.QFont()
        font.setPointSize(14)
        self.userLabel.setFont(font)
        self.userLabel.setObjectName("userLabel")
        self.userPushButton = QtWidgets.QPushButton(self.centralwidget)
        self.userPushButton.setGeometry(QtCore.QRect(650, 20, 121, 31))
        self.userPushButton.setObjectName("userPushButton")
        MainWindow.setCentralWidget(self.centralwidget)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Типография"))
        self.userLabel.setText(_translate("MainWindow", "Вы не авторизованы"))
        self.userPushButton.setText(_translate("MainWindow", "Войти"))