from flask_sqlalchemy import SQLAlchemy
from dataclasses import dataclass
 
db = SQLAlchemy()

@dataclass
class ReviewModel(db.Model):
    __tablename__ = 'reviews'

    id: int
    name: str
    comment: str
 
    id = db.Column(db.Integer, primary_key = True)
    name = db.Column(db.String())
    comment = db.Column(db.String())
 
    def __init__(self, name, comment):
        self.name = name
        self.comment = comment
 
    def __repr__(self):
        return f"{self.name}:{self.comment}"

@dataclass
class UserModel(db.Model):
    __tablename__ = 'users'

    id: int
    name: str
    password: str
 
    id = db.Column(db.Integer, primary_key = True)
    name = db.Column(db.String())
    password = db.Column(db.String())
 
    def __init__(self, name, password):
        self.name = name
        self.password = password
 
    def __repr__(self):
        return f"{self.name}:{self.password}"
