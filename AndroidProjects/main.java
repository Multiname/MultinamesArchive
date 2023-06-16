package com.blackline.lw3_2_7;

import android.database.Cursor;
import android.os.Bundle;
import android.provider.MediaStore;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainActivity extends AppCompatActivity {

    ArrayList paths = null;
    ArrayList names= null;
    List<Map<String, Object>> listItems;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        GetImagesPath();
        Log.i("GetImagesPath", "onCreate: listItems.size " + listItems.size());
    }

    void GetImagesPath(){

        paths = new ArrayList();
        names = new ArrayList();

        Cursor cursor = getContentResolver().query(
                MediaStore.Images.Media.EXTERNAL_CONTENT_URI, null, null, null, null);
        while (cursor.moveToNext()) {
            //Get the name of the picture
            String name = cursor.getString(cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DISPLAY_NAME));
            // Get the absolute path of the picture
            int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);
            String path = cursor.getString(column_index);


            paths.add(path);
            names.add(name);

            Log.i("GetImagesPath", "GetImagesPath: name = "+name+"  path = "+ path);


        }
        listItems = new ArrayList<>();
        for (int i = 0; i < paths.size(); i++) {
            Map<String, Object> map = new HashMap<>();
            map.put("name", paths.get(i));
            map.put("desc", names.get(i));
            listItems.add(map);
        }
    }
}