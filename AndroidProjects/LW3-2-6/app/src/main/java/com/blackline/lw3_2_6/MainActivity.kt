package com.blackline.lw3_2_6

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.EditText

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
    }

    fun onClick(view: View) {
        startActivity(Intent(this,
            ListActivity::class.java).apply {
            putExtra("callerName",
                findViewById<EditText>(R.id.callerEditText).text.toString())
        })
    }
}