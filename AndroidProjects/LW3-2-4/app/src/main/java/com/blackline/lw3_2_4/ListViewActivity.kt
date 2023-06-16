package com.blackline.lw3_2_4

import android.annotation.SuppressLint
import android.content.Context
import android.database.Cursor
import android.database.DatabaseUtils
import android.database.sqlite.SQLiteDatabase
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.ListView
import android.widget.SimpleCursorAdapter
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import java.io.IOException
import java.io.OutputStreamWriter

class ListViewActivity : AppCompatActivity() {

    lateinit var header: TextView
    lateinit var list: ListView
    lateinit var databaseHelper: DatabaseHelper
    lateinit var db: SQLiteDatabase
    lateinit var cursor: Cursor
    lateinit var cursorAdapter: SimpleCursorAdapter

    private lateinit var query_name: String
    private lateinit var query: String


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_list_view)

        header = findViewById<View>(R.id.header) as TextView
        list = findViewById<View>(R.id.list) as ListView
        databaseHelper = DatabaseHelper(applicationContext)

        query_name = intent.extras!!.getString("query_name").toString()
        query = intent.extras!!.getString("query").toString()
    }

    @SuppressLint("Range")
    override fun onResume() {
        super.onResume()

        db = databaseHelper.readableDatabase
        cursor =  db.rawQuery(query, null)

        Log.i(query_name, DatabaseUtils.dumpCursorToString(cursor))

        if (query_name == "query2" || query_name == "query6" || query_name == "query7") {
            header.text = "List of data"

            val headers = arrayOf<String>(
                DatabaseHelper.COLUMN_FRP,
                DatabaseHelper.COLUMN_SQUARE,
                DatabaseHelper.COLUMN_WINDOWS,
                DatabaseHelper.COLUMN_SIGNALING,
                DatabaseHelper.COLUMN_TABLES,
                DatabaseHelper.COLUMN_COMPUTERS)

            cursorAdapter = SimpleCursorAdapter(
                this,
                R.layout.multi_line_list_item,
                cursor,
                headers,
                intArrayOf(R.id.line1, R.id.line2, R.id.line3,
                    R.id.line4, R.id.line5, R.id.line6),
                1)

            list.adapter = cursorAdapter
        } else if (query_name == "query1" || query_name == "query3") {
            header.text = "Data is in file"

            try {
                val outputStreamWriter = OutputStreamWriter(this.openFileOutput("$query_name.txt", Context.MODE_PRIVATE))
                outputStreamWriter.write(DatabaseUtils.dumpCursorToString(cursor))
                outputStreamWriter.close()
            } catch (e: IOException) {
                Log.e("Error", "$e")
            }
        } else if (query_name == "query4") {
            header.text = "Data is also in file"

            try {
                val outputStreamWriter = OutputStreamWriter(this.openFileOutput("$query_name.txt", Context.MODE_PRIVATE))
                outputStreamWriter.write(DatabaseUtils.dumpCursorToString(cursor))
                outputStreamWriter.close()
            } catch (e: IOException) {
                Log.e("Error", "$e")
            }

            val headers = arrayOf<String>(
                DatabaseHelper.COLUMN_FRP,
                "AVG(windows)")

            cursorAdapter = SimpleCursorAdapter(
                this,
                android.R.layout.two_line_list_item,
                cursor,
                headers,
                intArrayOf(android.R.id.text1, android.R.id.text2),
                1)

            list.adapter = cursorAdapter
        } else {
            header.text = "Data is in log"
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        db.close()
        cursor.close()
    }
}
