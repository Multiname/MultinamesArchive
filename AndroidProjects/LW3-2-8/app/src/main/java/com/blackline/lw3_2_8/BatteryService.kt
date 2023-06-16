package com.blackline.lw3_2_8

import android.app.Notification
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.Service
import android.content.Context
import android.content.Intent
import android.graphics.BitmapFactory
import android.graphics.Color
import android.os.BatteryManager
import android.os.Handler
import android.os.IBinder
import android.util.Log
import android.widget.Toast

class BatteryService : Service() {
    private var handler: Handler = Handler()
    private var previousCharge = 0.0
    private var speed = 0.0
    private var maxCapacity = 0.0
    private var isNotified = false
    private lateinit var batteryManager : BatteryManager

    lateinit var notificationManager: NotificationManager
    lateinit var notificationChannel: NotificationChannel
    lateinit var builder: Notification.Builder
    private val channelId = "i.apps.notifications"
    private val description = "Test notification"

    private val chargeRunnable = object : Runnable {
        override fun run() {
            val batteryLevelMilliAmpere = batteryManager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CHARGE_COUNTER) / 1000.0
            val dischargeSpeed = (previousCharge - batteryLevelMilliAmpere) * 60 / 3 / maxCapacity * 100
            previousCharge = batteryLevelMilliAmpere

            if (dischargeSpeed != 0.0) {
                if (dischargeSpeed > speed && !isNotified) {
                    isNotified = true
                    notificationManager.notify(1234, builder.build())
                }

                Log.d("ChargeSpeed", "Скорость разрядки %/min: $dischargeSpeed")
            }

            handler.postDelayed(this, 3000)
        }
    }

    override fun onBind(intent: Intent): IBinder? {
        return null
    }

    override fun onCreate() {
        super.onCreate()

        notificationManager = getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager

        notificationChannel = NotificationChannel(channelId, description, NotificationManager.IMPORTANCE_HIGH)
        notificationChannel.enableLights(true)
        notificationChannel.lightColor = Color.GREEN
        notificationChannel.enableVibration(false)
        notificationManager.createNotificationChannel(notificationChannel)

        builder = Notification.Builder(this, channelId)
            .setSmallIcon(R.drawable.ic_launcher_foreground)
            .setLargeIcon(BitmapFactory.decodeResource(this.resources, R.drawable.ic_launcher_foreground))
            .setContentTitle("The phone discharges")
            .setContentText("Your discharge limits has been exceeded")

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
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        speed = intent?.extras!!.getString("speed")!!.toDouble()

        val batteryLevelMilliAmpere = batteryManager.getIntProperty(BatteryManager.BATTERY_PROPERTY_CHARGE_COUNTER) / 1000.0
        previousCharge = batteryLevelMilliAmpere
        chargeRunnable.run()

        Toast.makeText(this, "Battery service has been started", Toast.LENGTH_SHORT).show()
        return super.onStartCommand(intent, flags, startId)
    }

    override fun onDestroy() {
        super.onDestroy()

        handler.removeCallbacks(chargeRunnable)
        Toast.makeText(this, "Battery service has been stopped", Toast.LENGTH_SHORT).show()
    }
}