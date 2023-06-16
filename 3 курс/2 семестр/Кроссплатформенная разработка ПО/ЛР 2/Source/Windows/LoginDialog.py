from PyQt5 import QtWidgets, QtCore
from Widgets.LoginDialogWidget import Ui_LoginDialogWidget
from Windows.SignUpDialog import SignUpDialog
from Db.Models.Automap import get_db_session, engine, Clients, Admins

class LoginDialog(QtWidgets.QDialog):
    def __init__(self):
        super(LoginDialog, self).__init__()
        self.ui = Ui_LoginDialogWidget()
        self.ui.setupUi(self)
        self.setModal(True)
        self.setWindowFlags(self.windowFlags() & ~QtCore.Qt.WindowContextHelpButtonHint)
        
        self.clientId = None
        self.adminId = None

        self.ui.loginPushButton.clicked.connect(self.Login)
        self.ui.SignupPushButton.clicked.connect(self.SignUp)
    
    def Login(self):
        with get_db_session(engine) as session:
            client = session.query(Clients).filter(
                Clients.name == self.ui.nameLineEdit.text()).first()
        with get_db_session(engine) as session:
            admin = session.query(Admins).filter(
                Admins.name == self.ui.nameLineEdit.text()).first()
        if (client == None and admin == None):
            self.ui.nameLineEdit.setStyleSheet("QLineEdit { background-color: red; }")
        else:
            if client != None and client.password == self.ui.passwordLineEdit.text():
                self.clientId = client.id
                self.clientName = client.name
                self.accept()
            elif admin.password == self.ui.passwordLineEdit.text():
                self.adminId = admin.id
                self.adminName = admin.name
                self.accept()
            else:
                self.ui.nameLineEdit.setStyleSheet("QLineEdit { background-color: white; }")
                self.ui.passwordLineEdit.setStyleSheet("QLineEdit { background-color: red; }")

    def SignUp(self):
        signUpDialog = SignUpDialog()
        signUpDialog.exec_()