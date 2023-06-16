from PyQt5 import QtWidgets, QtCore
from Widgets.AddProductDialogWidget import Ui_AddProductDialogWidget
from Db.Models.Automap import engine, Products
from sqlalchemy import insert

class AddProductDialog(QtWidgets.QDialog):
    def __init__(self):
        super(AddProductDialog, self).__init__()
        self.ui = Ui_AddProductDialogWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)

        self.ui.addPushButton.clicked.connect(self.AddProduct)
    
    def AddProduct(self):
        statement = insert(Products).values(name=self.ui.nameLineEdit.text(), price=self.ui.priceLineEdit.text())
        with engine.connect() as connect:
            connect.execute(statement)
            connect.commit()

        self.accept()