package com.blackline.lw3_2_3_1;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.widget.ImageButton;

import java.util.Random;

public class MainActivity extends AppCompatActivity {
    Integer alignment = Gravity.CENTER;
    Integer size = 12;
    Integer color = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Random random = new Random();
        findViewById(R.id.randomImageButton).setBackgroundColor(Color.rgb(
                random.nextInt(255), random.nextInt(255), random.nextInt(255)));
    }

    public void onAlignmentButtonClicked(View view)
    {
        switch (view.getId())
        {
            case R.id.rightButton:
                alignment = Gravity.RIGHT;
                break;
            case R.id.centerButton:
                alignment = Gravity.CENTER;
                break;
            case R.id.leftButton:
                alignment = Gravity.LEFT;
                break;
        }
    }

    public void onSizeButtonClicked(View view)
    {
        switch (view.getId())
        {
            case R.id.radioButtonSize_1:
                size = 12;
                break;
            case R.id.radioButtonSize_2:
                size = 14;
                break;
            case R.id.radioButtonSize_3:
                size = 16;
                break;
            case R.id.radioButtonSize_4:
                size = 18;
                break;
            case R.id.radioButtonSize_5:
                size = 20;
                break;
            case R.id.radioButtonSize_6:
                size = 22;
                break;
        }
    }

    public void onColorClicked(View view)
    {
        color = ((ColorDrawable)view.getBackground()).getColor();
    }

    public void onResultButtonClicked(View view)
    {
        Intent intent = new Intent(this, SecondActivity.class);
        intent.putExtra("alignment", alignment);
        intent.putExtra("size", size);
        intent.putExtra("color", color);
        startActivity(intent);
    }
}