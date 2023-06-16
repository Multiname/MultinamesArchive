package com.blackline.lw3_2_6

import android.content.pm.PackageManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.ContactsContract
import android.widget.ListView
import android.widget.SimpleCursorAdapter
import androidx.core.app.ActivityCompat

class ListActivity : AppCompatActivity() {
    val columns = listOf<String>(
        ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME,
        ContactsContract.CommonDataKinds.Phone.NUMBER,
        ContactsContract.CommonDataKinds.Phone._ID
    ).toTypedArray()

    lateinit var cursorAdapter: SimpleCursorAdapter
    lateinit var callerName: String
    lateinit var resultListView: ListView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_list)

        resultListView = findViewById<ListView>(R.id.resultListView)
        callerName = intent.extras!!.getString("callerName").toString()

        if (ActivityCompat.checkSelfPermission(this,
                android.Manifest.permission.READ_CONTACTS) !=
            PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this, Array(1){
                android.Manifest.permission.READ_CONTACTS
            }, 1111)
        } else GetContacts()
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)

        if (requestCode == 1111 &&
            grantResults[0] == PackageManager.PERMISSION_GRANTED)
            GetContacts()
    }

    fun GetContacts() {
        var from = listOf<String>(
            ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME,
            ContactsContract.CommonDataKinds.Phone.NUMBER).toTypedArray()

        var cursor = contentResolver.query(
            ContactsContract.CommonDataKinds.Phone.CONTENT_URI,
            columns,
            "${ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME_ALTERNATIVE.split("\\s".toRegex()).toTypedArray()[0]} LIKE ? ",
            Array(1){"%$callerName%"},
            ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME
        )

        cursorAdapter = SimpleCursorAdapter(
            this,
            android.R.layout.two_line_list_item,
            cursor,
            from,
            intArrayOf(android.R.id.text1, android.R.id.text2),
            0
        )
        resultListView.adapter = cursorAdapter
    }
}