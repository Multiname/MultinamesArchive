from flask import Flask
from flask_migrate import Migrate
from models import db

from reviews import reviews
from users import users

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = "postgresql://postgres:2458173671@localhost:5432/LifeformDB"
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db.init_app(app)
migrate = Migrate(app, db)

app.register_blueprint(reviews, url_prefix='/reviews')
app.register_blueprint(users, url_prefix='/users')

if __name__ == '__main__':
    app.run(debug=True)
