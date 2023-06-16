package com.blackline.lw3_2_4

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper

class DatabaseHelper(context: Context?) : SQLiteOpenHelper(context, DATABASE_NAME, null, SCHEMA) {

    companion object {
        private const val DATABASE_NAME = "app.db"
        private const val SCHEMA = 1
        const val TABLE = "classrooms"

        const val COLUMN_ID = "_id"
        const val COLUMN_FRP = "frp"
        const val COLUMN_SQUARE = "square"
        const val COLUMN_WINDOWS = "windows"
        const val COLUMN_SIGNALING = "signaling"
        const val COLUMN_TABLES = "tables"
        const val COLUMN_COMPUTERS = "computers"
    }


    override fun onCreate(db: SQLiteDatabase) {
        db.execSQL("CREATE TABLE $TABLE (" +
                "$COLUMN_ID INTEGER PRIMARY KEY AUTOINCREMENT," +
                "$COLUMN_FRP TEXT, " +
                "$COLUMN_SQUARE REAL, " +
                "$COLUMN_WINDOWS INTEGER, " +
                "$COLUMN_SIGNALING BIT, " +
                "$COLUMN_TABLES INTEGER, " +
                "$COLUMN_COMPUTERS INTEGER);")

        val insertString = "INSERT INTO $TABLE ($COLUMN_FRP, $COLUMN_SQUARE, $COLUMN_WINDOWS, " +
                "$COLUMN_SIGNALING, $COLUMN_TABLES, $COLUMN_COMPUTERS) "
        db.execSQL(insertString + "VALUES ('Ivanov', 14.0, 4, 1, 18, 6);")
        db.execSQL(insertString + "VALUES ('Petrov', 15.0, 3, 0, 14, 3);")
        db.execSQL(insertString + "VALUES ('Nikitov', 13.5, 4, 1, 12, 2);")
        db.execSQL(insertString + "VALUES ('Andreev', 12.0, 2, 1, 15, 4);")
        db.execSQL(insertString + "VALUES ('Andreev', 14.2, 5, 0, 13, 3);")
        db.execSQL(insertString + "VALUES ('Ivanov', 16.0, 5, 1, 20, 8);")
        db.execSQL(insertString + "VALUES ('Nikitov', 12.3, 2, 0, 21, 8);")
        db.execSQL(insertString + "VALUES ('Nikitov', 13.6, 2, 1, 13, 2);")
        db.execSQL(insertString + "VALUES ('Ivanov', 14.1, 1, 0, 18, 8);")
        db.execSQL(insertString + "VALUES ('Petrov', 16.2, 4, 1, 15, 5);")
        db.execSQL(insertString + "VALUES ('Ivanov', 12.8, 3, 0, 12, 1);")
        db.execSQL(insertString + "VALUES ('Andreev', 13.2, 4, 0, 19, 7);")
        db.execSQL(insertString + "VALUES ('Petrov', 14.2, 3, 1, 22, 10);")
        db.execSQL(insertString + "VALUES ('Nikitov', 11.0, 2, 0, 14, 0);")
        db.execSQL(insertString + "VALUES ('Petrov', 15.3, 4, 1, 17, 2);")
    }

    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
        db.execSQL("DROP TABLE IF EXISTS $TABLE")
        onCreate(db)
    }
}
