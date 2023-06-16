package com.blackline.lw3_2_3_1;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.Gravity;
import android.widget.TextView;

public class SecondActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);

        Intent intent = getIntent();
        TextView textView =  findViewById(R.id.textView);
        textView.setGravity(intent.getIntExtra("alignment", Gravity.CENTER));
        textView.setTextSize(intent.getIntExtra("size", 12));
        textView.setTextColor(intent.getIntExtra("color", 0));
    }
}