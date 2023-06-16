from contextlib import contextmanager
from sqlalchemy.ext.automap import automap_base
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker

engine = create_engine("postgresql+psycopg2://postgres:2458173671@localhost:5432/postgres",
                       future=True)
Base = automap_base()

Base.prepare(autoload_with=engine)

Clients = Base.classes.clients
Contracts = Base.classes.contracts
Products = Base.classes.products
Admins = Base.classes.admins

@contextmanager
def get_db_session(engine):
    SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
    db = SessionLocal()
    try:
        yield db
    except Exception:
        db.rollback()
        raise
    finally:
        db.close()
