package com.blackline.lw3_2_8

import android.content.Context
import android.content.Intent
import android.os.BatteryManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.view.View
import android.widget.EditText
import android.widget.TextView
import java.text.DecimalFormat

class MainActivity : AppCompatActivity() {
    private var handler: Handler = Handler()
    private var previousCharge = 0.0
    private var maxCapacity = 0.0
    private lateinit var batteryManager : BatteryManager
    private lateinit var chargeTextView : TextView

    private val chargeRunnable = object : Runnable {
        override fun run() {
            val batteryLevelMilliAmpere = batteryManager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CHARGE_COUNTER) / 1000.0
            val dischargeSpeed = (previousCharge - batteryLevelMilliAmpere) * 60 / 3 / maxCapacity * 100
            previousCharge = batteryLevelMilliAmpere

            chargeTextView.text = "${DecimalFormat("#.###").format(dischargeSpeed)} %/min"

            handler.postDelayed(this, 3000)
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        chargeTextView = findViewById<TextView>(R.id.chargeTextView)

        batteryManager = getSystemService(Context.BATTERY_SERVICE) as BatteryManager

        val mPowerProfile: Any
        var batteryCapacity = 0.0
        val POWER_PROFILE_CLASS = "com.android.internal.os.PowerProfile"
        try {
            mPowerProfile = Class.forName(POWER_PROFILE_CLASS)
                .getConstructor(Context::class.java)
                .newInstance(this.applicationContext)
            batteryCapacity = Class
                .forName(POWER_PROFILE_CLASS)
                .getMethod("getBatteryCapacity")
                .invoke(mPowerProfile) as Double
        } catch (e: Exception) {
            e.printStackTrace()
        }

        maxCapacity = batteryCapacity

        val batteryLevelMilliAmpere = batteryManager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CHARGE_COUNTER) / 1000.0
        previousCharge = batteryLevelMilliAmpere
        chargeRunnable.run()
    }

    fun onStartButtonClick(view: View) {
        val speedTextView = findViewById<EditText>(R.id.speedEditTextNumberDecimal)
        val speed = speedTextView.text.toString()
        if (speed != "")
            startService(Intent(this@MainActivity, BatteryService::class.java).apply {
                putExtra(
                    "speed",
                    speed
                )
            })
    }

    fun onStopButtonClick(view: View) {
        stopService(Intent(this@MainActivity, BatteryService::class.java))
    }

    override fun onDestroy() {
        super.onDestroy()

        handler.removeCallbacks(chargeRunnable)
    }
}