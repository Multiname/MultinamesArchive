from PyQt5 import QtWidgets, QtCore
from Widgets.AdminPanelWindowWidget import Ui_AdminPanelWindowWidget
from Db.Models.Automap import get_db_session, engine, Clients, Contracts, Products
from PyQt5.QtWidgets import QTableWidgetItem, QPushButton, QHeaderView, QInputDialog

class AdminPanelWindow(QtWidgets.QDialog):
    def __init__(self):
        super(AdminPanelWindow, self).__init__()
        self.ui = Ui_AdminPanelWindowWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)

        self.exit = False

        self.LoadClients()
        self.LoadContracts()

        self.ui.exitPushButton.clicked.connect(self.Exit)


    def LoadClients(self):        
        with get_db_session(engine) as session:
            self.clients = sorted(session.query(Clients).all(), key=lambda x: x.id)

        self.ui.clientsTableWidget.setColumnCount(5)
        self.ui.clientsTableWidget.setHorizontalHeaderLabels(
            ("Клиент", "Номер", "Скидка", "", "")
        )

        header = self.ui.clientsTableWidget.horizontalHeader()
        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(3, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(4, QHeaderView.ResizeToContents)
        
        count = len(self.clients)
        self.ui.clientsTableWidget.setRowCount(count)
            
        for i in range(count):
            item = QTableWidgetItem(self.clients[i].name)
            self.ui.clientsTableWidget.setItem(i, 0, item)

            item = QTableWidgetItem(str(self.clients[i].phonenumber))
            self.ui.clientsTableWidget.setItem(i, 1, item)

            item = QTableWidgetItem(str(self.clients[i].sale))
            self.ui.clientsTableWidget.setItem(i, 2, item)

            item = QPushButton(self)
            item.setObjectName("EditSaleButton_" + str(self.clients[i].id))
            item.setText("Изменить скидку")
            item.clicked.connect(lambda ignore, id=self.clients[i].id: self.ChangeSale(id))
            self.ui.clientsTableWidget.setCellWidget(i, 3, item)

            item = QPushButton(self)
            item.setObjectName("DeleteClientButton_" + str(self.clients[i].id))
            item.setText("Удалить")
            item.clicked.connect(lambda ignore, id=self.clients[i].id: self.DeleteClient(id))
            self.ui.clientsTableWidget.setCellWidget(i, 4, item)
    
    def ChangeSale(self, id):
        sale, ok = QInputDialog.getText(self, 'Изменение скидки', 'Новая скидка', flags=QtCore.Qt.WindowCloseButtonHint)

        if ok:
            sale = float(sale)
            with get_db_session(engine) as session:
                session.query(Clients).filter(Clients.id == id).update({
                    "sale": sale
                })
                session.commit()
                
            self.LoadClients()
    
    def DeleteClient(self, id):
        with get_db_session(engine) as session:
            session.query(Clients).filter(Clients.id == id).delete()
            session.commit()
        self.LoadClients()

    def LoadContracts(self):
        with get_db_session(engine) as session:
            self.contracts = sorted(session.query(Contracts).all(), key=lambda x: x.id)

        self.ui.contractsTableWidget.setColumnCount(6)
        self.ui.contractsTableWidget.setHorizontalHeaderLabels(
            ("Клиент", "Товар", "Кол-во", "Сумма, р.", "", "")
        )

        header = self.ui.contractsTableWidget.horizontalHeader()
        header.setSectionResizeMode(0, QHeaderView.Stretch)
        header.setSectionResizeMode(1, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(2, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(3, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(4, QHeaderView.ResizeToContents)
        header.setSectionResizeMode(5, QHeaderView.ResizeToContents)
        
        count = len(self.contracts)
        self.ui.contractsTableWidget.setRowCount(count)
            
        for i in range(count):
            with get_db_session(engine) as session:
                client = session.query(Clients).filter(
                    Clients.id == self.contracts[i].clientid).first()
                item = QTableWidgetItem(client.name if client != None else "None")
                self.ui.contractsTableWidget.setItem(i, 0, item)

            with get_db_session(engine) as session:
                product = session.query(Products).filter(
                    Products.id == self.contracts[i].productid).first()
                item = QTableWidgetItem(product.name if product != None else "None")
                self.ui.contractsTableWidget.setItem(i, 1, item)

            item = QTableWidgetItem(str(self.contracts[i].count))
            self.ui.contractsTableWidget.setItem(i, 2, item)

            item = QTableWidgetItem(str(self.contracts[i].amount))
            self.ui.contractsTableWidget.setItem(i, 3, item)

            item = QPushButton(self)
            item.setObjectName("EditCountButton_" + str(self.contracts[i].id))
            item.setText("Изменить кол-во")
            item.clicked.connect(lambda ignore, id=self.contracts[i].id: self.ChangeCount(id))
            self.ui.contractsTableWidget.setCellWidget(i, 4, item)

            item = QPushButton(self)
            item.setObjectName("DeleteContractButton_" + str(self.contracts[i].id))
            item.setText("Удалить")
            item.clicked.connect(lambda ignore, id=self.contracts[i].id: self.DeleteContract(id))
            self.ui.contractsTableWidget.setCellWidget(i, 5, item)
    
    def ChangeCount(self, id):
        count, ok = QInputDialog.getText(self, 'Изменение количества', 'Новое количество', flags=QtCore.Qt.WindowCloseButtonHint)

        if ok:
            count = int(count)
            with get_db_session(engine) as session:
                session.query(Contracts).filter(Contracts.id == id).update({
                    "count": count
                })
                session.commit()
                
            self.LoadContracts()
    
    def DeleteContract(self, id):
        with get_db_session(engine) as session:
            session.query(Contracts).filter(Contracts.id == id).delete()
            session.commit()
        self.LoadContracts()

    def Exit(self):
        self.exit = True
        self.close()