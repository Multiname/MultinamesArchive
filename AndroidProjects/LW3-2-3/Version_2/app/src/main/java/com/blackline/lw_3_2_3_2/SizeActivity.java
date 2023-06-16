package com.blackline.lw_3_2_3_2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class SizeActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_size);
    }

    public void onSizeButtonClicked(View view)
    {
        Integer size = 12;

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

        Intent intent = new Intent();
        intent.putExtra("size", size);
        setResult(RESULT_OK, intent);
        finish();
    }
}