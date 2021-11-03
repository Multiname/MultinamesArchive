class Password():
    def __init__(self, nickname, pin, password):
        self.nickname = nickname
        self.pin = pin
        self.password = password
        
    def Coincidence(self, password):
        return password == self.pin or password == self.password
    
    nickname = str
    pin = int
    password = str

password = Password("Bob", 1234, "qwerty")
print(password.Coincidence(1234))
print(password.Coincidence("qwerty"))
print(password.Coincidence(0))
