package com.blackline.lw3_2_5

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ArrayAdapter
import android.widget.GridView
import androidx.core.view.get

class ListActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_list)

        val gridView = findViewById<GridView>(R.id.gridView)
        val numColumns = intent.extras!!.getString("numColumns").toString()
        val horizontalSpacing = intent.extras!!.getString("horizontalSpacing").toString()
        val color = intent.getIntExtra("color", 0)

        var agents = arrayOf("Viper", "Cypher", "Phoenix", "Skye", "KAY/O", "Omen")
        val adapter = ArrayAdapter(this, android.R.layout.simple_list_item_1, agents)

        gridView.adapter = adapter
        gridView.numColumns = numColumns.toInt()
        gridView.horizontalSpacing = horizontalSpacing.toInt()

        gridView.setOnItemClickListener{ parent, v, position, id ->
            val selected = parent.getItemAtPosition(position).toString()
            for (i in 0 until parent.count) {
                parent[i].apply {
                    if (i != position) {
                        setBackgroundColor(0)
                    } else {
                        setBackgroundColor(color)
                    }
                }
            }
        }
    }
}