package com.blackline.lw_3_2_3_2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void changeAlignment(View view){
        Intent intent = new Intent("android.intent.action.ChangeTextAlingment");
        startActivityForResult(intent, 1);
    }

    public void changeSize(View view){
        Intent intent = new Intent("android.intent.action.ChangeSize");
        startActivityForResult(intent, 2);
    }

    public void changeColor(View view){
        Intent intent = new Intent("android.intent.action.ChangeColor");
        startActivityForResult(intent, 3);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        TextView textView = findViewById(R.id.textView);
        if (data == null) {return;}
        if (resultCode != RESULT_OK) {return;}
        switch (requestCode){
            case 1:
                Integer alignment = data.getIntExtra("alignment", Gravity.CENTER);
                textView.setGravity(alignment);
                break;
            case 2:
                Integer size = data.getIntExtra("size", 12);
                textView.setTextSize(size);
                break;
            case 3:
                Integer color = data.getIntExtra("color", 0);
                textView.setTextColor(color);
                break;
        }
    }
}