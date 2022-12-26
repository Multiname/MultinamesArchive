from flask import Blueprint

from flask import Flask, request, jsonify
from models import db, UserModel

users = Blueprint('users', __name__)

@users.route('/login', methods = ['POST'])
def Login():
    if request.method == 'POST':
        res = UserModel.query.filter_by(name=request.form['login'],
                                          password=request.form['password']).first()
        response = jsonify(res)
        response.headers.add("Access-Control-Allow-Origin", "*")
        return response
    return jsonify(None)

@users.route('/signup', methods = ['POST'])
def Signup():
    if request.method == 'POST':
        res = UserModel.query.filter_by(name=request.form['login']).first()
        if res == None:
            login = request.form['login']
            password = request.form['password']
            user = UserModel(name=login, password=password)
            db.session.add(user)
            db.session.commit()
            response = jsonify(user)
            response.headers.add("Access-Control-Allow-Origin", "*")
            return response
    return jsonify(None)
