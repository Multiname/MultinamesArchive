from PyQt5 import QtWidgets, QtCore
from Widgets.MainWindowWidget import Ui_MainWindowWidget
from PyQt5.QtWidgets import QTableWidgetItem, QPushButton, QSpinBox, QMessageBox, QInputDialog, QHeaderView
from Db.Models.Automap import get_db_session, engine, Products, Contracts
from Windows.LoginDialog import LoginDialog
from Windows.ProfileWindow import ProfileWindow
from Windows.AddProductDialog import AddProductDialog
from Windows.AdminPanelWindow import AdminPanelWindow

class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindowWidget()
        self.ui.setupUi(self)

        self.isLogged = False
        self.isAdmin = False

        self.LoadProducts()
        self.ui.userPushButton.clicked.connect(self.Login)

    def LoadProducts(self):        
        with get_db_session(engine) as session:
            self.products = sorted(session.query(Products).all(), key=lambda x: x.id)

        header = self.ui.productsTableWidget.horizontalHeader()

        if self.isLogged:
            if self.isAdmin:
                self.ui.productsTableWidget.clear()
                self.ui.productsTableWidget.setColumnCount(5)
                self.ui.productsTableWidget.setHorizontalHeaderLabels(
                    ("Название", "Цена, р.", "", "", "")
                )
                header.setSectionResizeMode(2, QHeaderView.ResizeToContents)
                header.setSectionResizeMode(3, QHeaderView.ResizeToContents)
                header.setSectionResizeMode(4, QHeaderView.ResizeToContents)
            else:
                self.ui.productsTableWidget.setColumnCount(4)
                self.ui.productsTableWidget.setHorizontalHeaderLabels(
                    ("Название", "Цена, р.", "Кол-во", "")
                )
                header.setSectionResizeMode(2, QHeaderView.ResizeToContents)
                header.setSectionResizeMode(3, QHeaderView.ResizeToContents)
        else:
            self.ui.productsTableWidget.setColumnCount(2)
            self.ui.productsTableWidget.setHorizontalHeaderLabels(
                ("Название", "Цена, р.")
            )

        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        
        productCount = len(self.products)
        if self.isLogged and self.isAdmin:
            self.ui.productsTableWidget.setRowCount(productCount + 1)
        else:
            self.ui.productsTableWidget.setRowCount(productCount)
            
        for i in range(productCount):
            item = QTableWidgetItem(str(self.products[i].name))
            self.ui.productsTableWidget.setItem(i, 0, item)

            item = QTableWidgetItem(str(self.products[i].price))
            self.ui.productsTableWidget.setItem(i, 1, item)

            if self.isLogged:
                if self.isAdmin:
                    item = QPushButton(self)
                    item.setObjectName("EditNameButton_" + str(self.products[i].id))
                    item.setText("Изменить название")
                    item.clicked.connect(lambda ignore, id=self.products[i].id: self.ChangeProductName(id))
                    self.ui.productsTableWidget.setCellWidget(i, 2, item)

                    item = QPushButton(self)
                    item.setObjectName("EditPriceButton_" + str(self.products[i].id))
                    item.setText("Изменить цену")
                    item.clicked.connect(lambda ignore, id=self.products[i].id: self.ChangeProductPrice(id))
                    self.ui.productsTableWidget.setCellWidget(i, 3, item)

                    item = QPushButton(self)
                    item.setObjectName("DeleteButton_" + str(self.products[i].id))
                    item.setText("Удалить")
                    item.clicked.connect(lambda ignore, id=self.products[i].id: self.DeleteProduct(id))
                    self.ui.productsTableWidget.setCellWidget(i, 4, item)
                else:
                    spinBox = QSpinBox(self)
                    spinBox.setObjectName("BuySpinBox_" + str(self.products[i].id))
                    self.ui.productsTableWidget.setCellWidget(i, 2, spinBox)

                    item = QPushButton(self)
                    item.setObjectName("BuyButton_" + str(self.products[i].id))
                    item.setText("Купить")
                    item.clicked.connect(lambda ignore, id=self.products[i].id,
                                         name=self.products[i].name, sb=spinBox:
                                            self.Buy(id, name, sb.text()))
                    self.ui.productsTableWidget.setCellWidget(i, 3, item)
            
        if self.isLogged and self.isAdmin:
            item = QPushButton(self)
            item.setObjectName("AddButton")
            item.setText("Добавить")
            item.clicked.connect(self.AddProduct)
            self.ui.productsTableWidget.setCellWidget(productCount, 0, item)

    def Login(self):
        loginDialog = LoginDialog()
        if loginDialog.exec_() == QtWidgets.QDialog.Accepted:
            self.isLogged = True

            self.clientId = loginDialog.clientId
            self.adminId = loginDialog.adminId

            if self.clientId != None:
                self.clientName = loginDialog.clientName
                
                self.ui.userLabel.setText("Вы вошли как: " + self.clientName)
                self.LoadProducts()

                self.ui.userPushButton.setText("Личный кабинет")
                self.ui.userPushButton.clicked.disconnect(self.Login)
                self.ui.userPushButton.clicked.connect(self.OpenProfile)
            else:
                self.adminName = loginDialog.adminName
                self.isAdmin = True

                self.ui.userLabel.setText("Вы вошли как админ: " + self.adminName)
                self.LoadProducts()

                self.ui.userPushButton.setText("Панель")
                self.ui.userPushButton.clicked.disconnect(self.Login)
                self.ui.userPushButton.clicked.connect(self.OpenPanel)

    def Buy(self, id, name, count):
        buyAcceptanceMessageBox = QMessageBox()
        buyAcceptanceMessageBox.setIcon(QMessageBox.Question)
        buyAcceptanceMessageBox.setWindowTitle("Подтверждение покупки")
        buyAcceptanceMessageBox.setText("Купить " + name + " в количестве " + count + "?")
        buyAcceptanceMessageBox.setStandardButtons(QMessageBox.Yes | QMessageBox.No)
        result = buyAcceptanceMessageBox.exec()

        if result == QMessageBox.Yes:
            with get_db_session(engine) as session:
                contract = Contracts(clientid=self.clientId, productid=id, count=count)
                session.add(contract)
                session.commit()

    def OpenProfile(self):
        profileWindow = ProfileWindow(self.clientId)
        profileWindow.exec_()
        if profileWindow.name != self.clientName:
            self.clientName = profileWindow.name
            self.ui.userLabel.setText("Вы вошли как: " + self.clientName)

        if profileWindow.exit:
            self.clientId = None
            self.clientName = None
            self.isLogged = False
            self.ui.userLabel.setText("Вы не авторизованы")
            self.ui.userPushButton.setText("Войти")
            self.ui.userPushButton.clicked.connect(self.Login)
            self.ui.userPushButton.clicked.disconnect(self.OpenProfile)
            self.LoadProducts()

    def ChangeProductName(self, productId):
        name, ok = QInputDialog.getText(self, 'Изменение названия', 'Новое название', flags=QtCore.Qt.WindowCloseButtonHint)

        if ok:
            with get_db_session(engine) as session:
                session.query(Products).filter(Products.id == productId).update({
                    "name": name
                })
                session.commit()
                
            self.LoadProducts()

    def ChangeProductPrice(self, productId):
        price, ok = QInputDialog.getText(self, 'Изменение цены', 'Новая цена', flags=QtCore.Qt.WindowCloseButtonHint)

        if ok:
            price = float(price)
            with get_db_session(engine) as session:
                session.query(Products).filter(Products.id == productId).update({
                    "price": price
                })
                session.commit()
                
            self.LoadProducts()

    def DeleteProduct(self, productId):
        with get_db_session(engine) as session:
            session.query(Products).filter(Products.id == productId).delete()
            session.commit()
        self.LoadProducts()

    def AddProduct(self):
        addProductDialog = AddProductDialog()
        if addProductDialog.exec_() == QtWidgets.QDialog.Accepted:
            self.LoadProducts()

    def OpenPanel(self):
        adminPanelWindow = AdminPanelWindow()
        adminPanelWindow.exec_()

        if adminPanelWindow.exit:
            self.adminId = None
            self.adminName = None
            self.isLogged = False
            self.isAdmin = False
            self.ui.userLabel.setText("Вы не авторизованы")
            self.ui.userPushButton.setText("Войти")
            self.ui.userPushButton.clicked.connect(self.Login)
            self.ui.userPushButton.clicked.disconnect(self.OpenPanel)
            self.LoadProducts()