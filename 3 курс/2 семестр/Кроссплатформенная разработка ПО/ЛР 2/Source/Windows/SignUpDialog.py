from PyQt5 import QtWidgets, QtCore
from Widgets.SignUpDialogWidget import Ui_SignUpDialogWidget
from Db.Models.Automap import engine, Clients, get_db_session, Admins
from sqlalchemy import insert

class SignUpDialog(QtWidgets.QDialog):
    def __init__(self):
        super(SignUpDialog, self).__init__()
        self.ui = Ui_SignUpDialogWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        
        self.ui.SignupPushButton.clicked.connect(self.SignUp)

    def SignUp(self):
        with get_db_session(engine) as session:
            client = session.query(Clients).filter(
                Clients.name == self.ui.nameLineEdit.text()).first()
        with get_db_session(engine) as session:
            admin = session.query(Admins).filter(
                Admins.name == self.ui.nameLineEdit.text()).first()
        if (client != None or admin != None):
            self.ui.nameLineEdit.setStyleSheet("QLineEdit { background-color: red; }")
        else:
            statement = insert(Clients).values(name=self.ui.nameLineEdit.text(), password=self.ui.passwordLineEdit.text(),
                                               phonenumber=self.ui.phoneLineEdit.text(), sale=0)
            with engine.connect() as connect:
                connect.execute(statement)
                connect.commit()

        self.accept()