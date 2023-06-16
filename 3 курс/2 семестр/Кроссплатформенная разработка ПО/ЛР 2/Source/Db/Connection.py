from configparser import ConfigParser
import psycopg2
from sqlalchemy import create_engine

class DatabaseConfig():
    def __init__(self, filename='config.ini', section='postgresql'):
        parser = ConfigParser()
        parser.read(filename)

        self.params = {}
        if parser.has_section(section):
            params = parser.items(section)
            for param in params:
                self.params[param[0]] = param[1]
        else:
            raise Exception(
                'Section {0} not found in the {1} file'.format(section, filename))

class Connection():
    def __init__(self, config: DatabaseConfig = DatabaseConfig()):
        self.connection: psycopg2.connection = None
        self.cursor: psycopg2.cursor = None
        self.params = config.params
        self.engine = create_engine(
            f"postgresql+psycopg2://{self.params['user']}:{self.params['password']}@{self.params['host']}:5432/{self.params['database']}", pool_size=10, max_overflow=20)

    def set_connection(f):
        def wrapper(*args):
            if args[0].connection is None or args[0].connection.closed:
                args[0].__connect()

            ret = f(*args)

            if args[0].connection is not None or not args[0].connection.closed:
                args[0].__close()
            return ret
        return wrapper

    def __connect(self):
        self.connection = psycopg2.connect(**self.params)
        self.cursor = self.connection.cursor()

    def __close(self):
        if self.cursor is not None:
            self.cursor.close()

        if self.connection is not None:
            self.connection.close()

    @set_connection
    def _execute(self, query: str, params: tuple = ()) -> str:
        if query.startswith("SELECT"):
            self.cursor.execute(query, params)
            data = self.cursor.fetchall()
            return data
        elif query.startswith(("UPDATE", "INSERT", "DELETE")):
            self.cursor.execute(query, params)
            self.connection.commit()

    @set_connection
    def _commit(self):
        self.connection.commit()

    @set_connection
    def _exists(self, query: str, params: tuple = ()):
        self.cursor.execute(query, params)
        return self.cursor.fetchone() is not None

    @set_connection
    def parse_table_names(self):
        self.cursor.execute(
            "SELECT tablename FROM pg_tables WHERE schemaname = 'public'",
            [])

        return tuple(map(lambda x: x[0], self.cursor.fetchall()))

    @set_connection
    def parse_column_names(self, name: str):
        self.cursor.execute(
            "SELECT COLUMN_NAME FROM information_schema.columns WHERE table_schema = 'public' AND table_name = %s", (
                name, )
        )

        return tuple(map(lambda x: x[0], self.cursor.fetchall()))

    @set_connection
    def parse_table_data(self, name: str):
        self.cursor.execute(
            f"SELECT * FROM {name}", []
        )

        return self.cursor.fetchall()
