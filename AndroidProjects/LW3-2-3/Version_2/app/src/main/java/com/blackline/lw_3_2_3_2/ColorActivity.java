package com.blackline.lw_3_2_3_2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.view.View;

import java.util.Random;

public class ColorActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_color);

        Random random = new Random();
        findViewById(R.id.randomImageButton).setBackgroundColor(Color.rgb(
                random.nextInt(255), random.nextInt(255), random.nextInt(255)));
    }

    public void onColorClicked(View view)
    {
        Intent intent = new Intent();
        intent.putExtra("color", ((ColorDrawable)view.getBackground()).getColor());
        setResult(RESULT_OK, intent);
        finish();
    }
}