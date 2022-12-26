from flask import Blueprint

from flask import Flask, request, jsonify
from models import db, ReviewModel

reviews = Blueprint('reviews', __name__)

@reviews.route('/', methods = ['POST', 'GET'])
def Review():
    if request.method == 'POST':
        name = request.form['name']
        comment = request.form['comment']
        review = ReviewModel(name=name, comment=comment)
        db.session.add(review)
        db.session.commit()
        return f"Done!"
    response = jsonify(ReviewModel.query.all())
    response.headers.add("Access-Control-Allow-Origin", "*")
    return response
