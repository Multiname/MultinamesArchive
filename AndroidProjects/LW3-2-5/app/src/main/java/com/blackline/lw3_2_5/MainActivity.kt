package com.blackline.lw3_2_5

import android.content.Intent
import android.graphics.drawable.ColorDrawable
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.ArrayAdapter
import android.widget.Spinner

class MainActivity : AppCompatActivity() {
    var color = 0
    var numColumns = arrayOf("1", "2", "3")
    var horizontalSpacing = arrayOf("10", "50", "100")

    lateinit var columnNumberSpinner: Spinner
    lateinit var horizontalSpacingSpinner: Spinner

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        columnNumberSpinner = findViewById<Spinner>(R.id.columnNumberSpinner)
        horizontalSpacingSpinner = findViewById<Spinner>(R.id.horizontalSpacingSpinner)

        val columnNumberAdapter = ArrayAdapter(this, android.R.layout.simple_spinner_item, numColumns)
        columnNumberAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        columnNumberSpinner.adapter = columnNumberAdapter

        val horizontalSpacingAdapter = ArrayAdapter(this, android.R.layout.simple_spinner_item, horizontalSpacing)
        horizontalSpacingAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        horizontalSpacingSpinner.adapter = horizontalSpacingAdapter
    }

    fun onColorClick(view: View) {
        color = (view.background as ColorDrawable).color
    }

    fun onDoneClick(view: View) {
        val intent = Intent(this, ListActivity::class.java).apply {
            putExtra("numColumns", columnNumberSpinner.selectedItem.toString())
            putExtra("horizontalSpacing", horizontalSpacingSpinner.selectedItem.toString())
            putExtra("color", color)
        }

        startActivity(intent)
    }
}