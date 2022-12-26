import sqlite3
from prettytable import PrettyTable

conn = sqlite3.connect('../SocialNetwork.db')
cur = conn.cursor()

def Select(tableName):
    try:
        pretTable = PrettyTable()
        sqlStr = "SELECT * from " + tableName
        cur.execute(sqlStr)
        all_results = cur.fetchall()
        names = list(map(lambda x: x[0], cur.description))
        pretTable.field_names = names
        for row in all_results:
            pretTable.add_row(row)
        print(pretTable)
    except sqlite3.Error as error:
        print("Ошибка: ", error)

def Insert(tableName):
    try:
        Select(tableName)
        sqlStr = "SELECT * from " + tableName
        cur.execute(sqlStr)
        res = cur.fetchone()
        addArr = []
        dividers = []
        names = list(map(lambda x: x[0], cur.description))
        for name in names:
            addArr.append(input("Введите поле '" + name + "': "))
        for i in range(0, len(names)):
            dividers.append('?')
        newString = f"insert into {tableName} values(" + \
            ', '.join(dividers) + ");"
        cur.execute(newString, addArr)
        conn.commit()
        Select(tableName)
    except sqlite3.Error as error:
        print("Ошибка: ", error)

def Delete(tableName):
    try:
        Select(tableName)
        colName = input(
            "Введите столбец для поиска: ")
        colValue = input("Значение столбца: ")
        cur.execute(f"DELETE FROM {tableName} WHERE {colName}='{colValue}';")
        conn.commit()
        Select(tableName)
    except sqlite3.Error as error:
        print("Ошибка: ", error)

def Update(tableName):
    try:
        Select(tableName)
        colId = input(
            "Введите ID элемента для изменения: ")
        sqlStr = "SELECT * from " + tableName
        cur.execute(sqlStr)
        res = cur.fetchone()
        names = list(map(lambda x: x[0], cur.description))
        cur.execute(
            f"SELECT * from {tableName} WHERE " + names[0] + f"={colId};")
        oldRec = cur.fetchone()
        updArr = []
        newUpdArr = []
        updStr = []
        print("Оставьте поля пустыми, если не хотите их менять")
        for name in names:
            updArr.append(input(f"Введите поле {name}: "))
        i = 0
        for elem in updArr:
            if elem != "":
                updStr.append(names[i] + " = ?")
                newUpdArr.append(elem)
            i += 1
        newSqlStr = f"UPDATE {tableName} set " + ', '.join(
            updStr) + f" WHERE {names[0]} == {oldRec[0]};"
        cur.execute(newSqlStr, newUpdArr)
        conn.commit()
        Select(tableName)
    except sqlite3.Error as error:
        print("Ошибка: ", error)

def RunMenu():
    exitCode = False
    while not exitCode:
        print("1. Вывести таблицу")
        print("2. Добавить в таблицу")
        print("3. Удалить из таблицы")
        print("4. Изменить запись в таблице")
        print("5. Выход")
        option = int(input(">>> "))
        print()
        validArr = [1, 2, 3, 4, 5]
        if (option not in validArr):
            print("Некорректный ввод")
            break
        if (option == 5):
            exitCode = True
            break
        else:
            tableName = input("Название таблицы: ")
            if (option == 1):
                Select(tableName)
            elif (option == 2):
                Insert(tableName)
            elif (option == 3):
                Delete(tableName)
            elif (option == 4):
                Update(tableName)
            input()

RunMenu()
