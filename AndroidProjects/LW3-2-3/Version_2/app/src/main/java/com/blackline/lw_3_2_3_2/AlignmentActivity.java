package com.blackline.lw_3_2_3_2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.view.Gravity;
import android.view.View;

public class AlignmentActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_alignment);
    }

    public void onAlignmentButtonClicked(View view)
    {
        int alignment = Gravity.CENTER;
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

        Intent intent = new Intent();
        intent.putExtra("alignment", alignment);
        setResult(RESULT_OK, intent);
        finish();
    }
}