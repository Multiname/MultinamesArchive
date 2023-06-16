from PyQt5 import QtWidgets, QtCore
from Widgets.ProfileWindowWidget import Ui_ProfileWindowWidget
from Db.Models.Automap import get_db_session, engine, Clients, Contracts, Products, Admins
from PyQt5.QtWidgets import QTableWidgetItem, QMessageBox, QHeaderView, QInputDialog

class ProfileWindow(QtWidgets.QDialog):
    def __init__(self, id):
        super(ProfileWindow, self).__init__()
        self.ui = Ui_ProfileWindowWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)

        self.id = id
        self.exit = False

        with get_db_session(engine) as session:
            client = session.query(Clients).filter(
                Clients.id == id).first()
            self.name = client.name
            self.password = client.password
            self.phone = client.phonenumber
            self.sale = client.sale

        self.ui.nameLabel.setText(self.name)
        self.ui.passwordLabel.setText(self.password)
        self.ui.phoneLabel.setText(str(self.phone))
        self.ui.saleLabel.setText("Скидка: " + str(self.sale) + "%")

        self.LoadContracts()

        self.ui.namePushButton.clicked.connect(self.ChangeName)
        self.ui.passwordPushButton.clicked.connect(self.ChangePassword)
        self.ui.phonePushButton.clicked.connect(self.ChangePhone)
        self.ui.exitPushButton.clicked.connect(self.Exit)

    def LoadContracts(self):        
        with get_db_session(engine) as session:
            self.contracts = session.query(Contracts).filter(Contracts.clientid == self.id).all()
        
        self.ui.contractsTableWidget.setColumnCount(3)
        self.ui.contractsTableWidget.setHorizontalHeaderLabels(
            ("Товар", "Кол-во", "Сумма, р.")
        )

        count = len(self.contracts)
        self.ui.contractsTableWidget.setRowCount(count)
        for i in range(count):
            with get_db_session(engine) as session:
                product = session.query(Products).filter(
                    Products.id == self.contracts[i].productid).first()
                item = QTableWidgetItem(product.name if product != None else "None")
                self.ui.contractsTableWidget.setItem(i, 0, item)

            item = QTableWidgetItem(str(self.contracts[i].count))
            self.ui.contractsTableWidget.setItem(i, 1, item)

            item = QTableWidgetItem(str(self.contracts[i].amount))
            self.ui.contractsTableWidget.setItem(i, 2, item)

        header = self.ui.contractsTableWidget.horizontalHeader()
        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)

    def ChangeName(self):
        name, ok = QInputDialog.getText(self, 'Изменение имени', 'Новое имя', flags=QtCore.Qt.WindowCloseButtonHint)

        if ok:
            with get_db_session(engine) as session:
                client = session.query(Clients).filter(
                    Clients.name == name).first()
            with get_db_session(engine) as session:
                admin = session.query(Admins).filter(
                    Admins.name == self.ui.nameLineEdit.text()).first()
            if (client != None or admin != None):
                takenLoginMessageBox = QMessageBox()
                takenLoginMessageBox.setIcon(QMessageBox.Critical)
                takenLoginMessageBox.setWindowTitle("Ошибка")
                takenLoginMessageBox.setText("Введенный логин уже занят")
                takenLoginMessageBox.setStandardButtons(QMessageBox.Ok)
                takenLoginMessageBox.exec()
                return

            with get_db_session(engine) as session:
                session.query(Clients).filter(Clients.id == self.id).update({
                    "name": name
                })
                session.commit()
                
            self.name = name
            self.ui.nameLabel.setText(name)

    def ChangePassword(self):
        password, ok = QInputDialog.getText(self, 'Изменение пароля', 'Новый пароль', flags=QtCore.Qt.WindowCloseButtonHint)
        if ok:
            with get_db_session(engine) as session:
                session.query(Clients).filter(Clients.id == self.id).update({
                    "password": password
                })
                session.commit()

            self.password = password
            self.ui.passwordLabel.setText(password)

    def ChangePhone(self):
        phone, ok = QInputDialog.getText(self, 'Изменение номера', 'Новый номер', flags=QtCore.Qt.WindowCloseButtonHint)
        if ok:
            phone = int(phone)
            with get_db_session(engine) as session:
                session.query(Clients).filter(Clients.id == self.id).update({
                    "phonenumber": phone
                })
                session.commit()

            self.phone = phone
            self.ui.phoneLabel.setText(str(phone))

    def Exit(self):
        self.exit = True
        self.close()