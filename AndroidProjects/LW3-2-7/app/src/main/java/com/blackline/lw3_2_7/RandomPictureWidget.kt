package com.blackline.lw3_2_7

import android.app.PendingIntent
import android.appwidget.AppWidgetManager
import android.appwidget.AppWidgetProvider
import android.content.ComponentName
import android.content.Context
import android.content.Intent
import android.net.Uri
import android.os.Handler
import android.os.Looper
import android.provider.MediaStore
import android.widget.RemoteViews

class RandomPictureWidget : AppWidgetProvider() {
    var imagePaths: List<String>? = null
    private val ACTION_WIDGET_CLICKED = "com.blackline.lw3_2_7.WIDGET_CLICKED"

    private val handler = Handler(Looper.getMainLooper())
    private lateinit var runnable: Runnable

    override fun onUpdate(context: Context, appWidgetManager: AppWidgetManager?, appWidgetIds: IntArray?) {
        super.onUpdate(context, appWidgetManager, appWidgetIds)

        if (imagePaths == null)
            imagePaths = getImagePaths(context)

        runnable = object : Runnable {
            override fun run() {
                val views = RemoteViews(context?.packageName, R.layout.random_picture_widget)

                views.setImageViewUri(R.id.widgetImageView, Uri.parse(imagePaths!![(0..9).random()]))

                appWidgetManager?.updateAppWidget(appWidgetIds, views)
                handler.postDelayed(this, 2000)
            }
        }
        handler.postDelayed(runnable, 0)

        val intent = Intent(context, RandomPictureWidget::class.java)
        intent.action = ACTION_WIDGET_CLICKED
        val pendingIntent = PendingIntent.getBroadcast(context, 0, intent, PendingIntent.FLAG_MUTABLE)

        val views = RemoteViews(context.packageName, R.layout.random_picture_widget)
        views.setOnClickPendingIntent(R.id.widgetImageView, pendingIntent)
        appWidgetManager?.updateAppWidget(appWidgetIds, views)
    }

    override fun onReceive(context: Context, intent: Intent) {
        super.onReceive(context, intent)

        if (intent.action?.equals(ACTION_WIDGET_CLICKED) == true) {
            val appWidgetManager = AppWidgetManager.getInstance(context)
            val appWidgetIds = appWidgetManager.getAppWidgetIds(
                ComponentName(context, RandomPictureWidget::class.java)
            )

            if (imagePaths == null)
                imagePaths = getImagePaths(context)

            val views = RemoteViews(context?.packageName, R.layout.random_picture_widget)

            views.setImageViewUri(R.id.widgetImageView, Uri.parse(imagePaths!![(0..9).random()]))

            appWidgetManager?.updateAppWidget(appWidgetIds, views)
        }
    }

    override fun onDisabled(context: Context?) {
        super.onDisabled(context)
        handler.removeCallbacks(runnable)
    }
}

internal fun getImagePaths(context: Context): List<String> {
    val imagePaths = mutableListOf<String>()
    val projection = arrayOf(MediaStore.Images.Media.DATA)
    val cursor = context.contentResolver.query(
        MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
        projection,
        null,
        null,
        MediaStore.Images.ImageColumns.DATE_MODIFIED + " DESC"
    )
    cursor!!.moveToFirst()
    while (!cursor.isAfterLast) {
        val pathIndex = cursor.getColumnIndex(MediaStore.Images.Media.DATA)
        val imagePath = cursor.getString(pathIndex)
        imagePaths.add(imagePath)
        cursor.moveToNext()
        if (imagePaths.count() >= 10) break
    }
    cursor.close()

    return imagePaths
}