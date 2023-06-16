package com.blackline.lw3_2_4

import android.content.Intent
import android.os.Bundle
import android.view.View
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        DatabaseHelper(applicationContext)
    }

    fun query1(view: View) {
        val intent = Intent(this, ListViewActivity::class.java).apply {
            putExtra("query_name", "query1")
            putExtra("query", "SELECT * FROM " + DatabaseHelper.TABLE +
                    " ORDER BY " + DatabaseHelper.COLUMN_COMPUTERS)
        }
        startActivity(intent)
    }

    fun query2(view: View) {
        val intent = Intent(this, ListViewActivity::class.java).apply {
            putExtra("query_name", "query2")
            putExtra("query", "SELECT * FROM (SELECT * FROM " + DatabaseHelper.TABLE +
                    " ORDER BY " + DatabaseHelper.COLUMN_SIGNALING + " ) ORDER BY " + DatabaseHelper.COLUMN_FRP)
        }
        startActivity(intent)
    }

    fun query3(view: View) {
        val intent = Intent(this, ListViewActivity::class.java).apply {
            putExtra("query_name", "query3")
            putExtra("query", "SELECT SUM(" + DatabaseHelper.COLUMN_TABLES
                    + ") FROM " + DatabaseHelper.TABLE)
        }
        startActivity(intent)
    }

    fun query4(view: View) {
        val intent = Intent(this, ListViewActivity::class.java).apply {
            putExtra("query_name", "query4")
            putExtra("query", "SELECT " + DatabaseHelper.COLUMN_ID + ", "
                    + DatabaseHelper.COLUMN_FRP + ", AVG(" + DatabaseHelper.COLUMN_WINDOWS + ") FROM "
                    + DatabaseHelper.TABLE + " GROUP BY " + DatabaseHelper.COLUMN_FRP)        }
        startActivity(intent)
    }

    fun query5(view: View) {
        val intent = Intent(this, ListViewActivity::class.java).apply {
            putExtra("query_name", "query5")
            putExtra("query", "SELECT * FROM " + DatabaseHelper.TABLE + " WHERE " +
                    DatabaseHelper.COLUMN_SQUARE + " = (SELECT MAX(" + DatabaseHelper.COLUMN_SQUARE
                    + ") FROM " + DatabaseHelper.TABLE + ")")
        }
        startActivity(intent)
    }

    fun query6(view: View) {
        val intent = Intent(this, ListViewActivity::class.java).apply {
            putExtra("query_name", "query6")
            putExtra("query", "SELECT * FROM " + DatabaseHelper.TABLE + " WHERE " +
                    DatabaseHelper.COLUMN_SQUARE + " > 13")
        }
        startActivity(intent)
    }

    fun query7(view: View) {
        val intent = Intent(this, ListViewActivity::class.java).apply {
            putExtra("query_name", "query7")
            putExtra("query", "SELECT * FROM " + DatabaseHelper.TABLE + " WHERE " +
                    DatabaseHelper.COLUMN_SQUARE + " < (SELECT AVG(" + DatabaseHelper.COLUMN_SQUARE
                    + ") FROM " + DatabaseHelper.TABLE + ")")
        }
        startActivity(intent)
    }

    fun query8(view: View) {
        val intent = Intent(this, ListViewActivity::class.java).apply {
            putExtra("query_name", "query8")
            putExtra("query", "SELECT * FROM " + DatabaseHelper.TABLE + " WHERE " +
                    DatabaseHelper.COLUMN_TABLES + " > 20 LIMIT 1")
        }
        startActivity(intent)
    }
}