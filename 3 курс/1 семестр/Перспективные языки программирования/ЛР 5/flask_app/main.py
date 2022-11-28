from flask import Flask, render_template, request, session, redirect, url_for, jsonify
import json

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/contacts')
def contacts():
    return render_template('contacts.html')

@app.route('/registration', methods=['GET', 'POST'])
def registration():
    if (request.method == 'POST'):
        data = {}
        with open('users.json') as json_file:
            data = json.load(json_file)
            data['users'].append({
                'login': request.form['login'],
                'password': request.form['password']
                })
        with open('users.json', 'w') as outfile:
            json.dump(data, outfile)
        return redirect(url_for('index'))
    else:
        return render_template('login.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if (request.method == 'POST'):
        with open('users.json') as json_file:
            data = json.load(json_file)
            for user in data['users']:
                if (user['login'] == request.form['login'] and
                    user['password'] == request.form['password']):
                    session['login'] = request.form['login']
                    session['password'] = request.form['password']
        return redirect(url_for('index'))
    else:
        return render_template('registration.html')

@app.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('index'))

@app.route('/create_review', methods=['POST'])
def create_review():
    if ("login" in session) and ("comment" in request.form):
        data = {}
        with open('reviews.json') as json_file:
            data = json.load(json_file)
            data['reviews'].append({
                'name': session['login'],
                'comment': request.form['comment']
                })
        with open('reviews.json', 'w') as outfile:
            json.dump(data, outfile)
        return jsonify({
            "response": "OK"
        })
    
    return jsonify({
        "response": "InvalidRequest"
    })


@app.route('/load_reviews', methods=['GET'])
def load_reviews():
    data = {}
    with open('reviews.json') as json_file:
        data = json.load(json_file)
    return jsonify({
        "response": "OK",
        "data": data
    })
    

app.secret_key = "qwerty"
app.run(debug = True, host='127.0.0.1', port='5050')
