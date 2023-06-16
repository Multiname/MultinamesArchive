package com.blackline.lw3_2_2;

import androidx.appcompat.app.AppCompatActivity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.RadioButton;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        TextView selectedText = findViewById(R.id.textView1);

        RadioButton radioButton2 = findViewById(R.id.radioButton2);
        RadioButton radioButton3 = findViewById(R.id.radioButton3);

        if(radioButton2.isChecked()) {
            selectedText = findViewById(R.id.textView2);
        } else if (radioButton3.isChecked()) {
            selectedText = findViewById(R.id.textView3);
        }

        switch(id){
            case R.id.small:
                selectedText.setTextSize(8);
                return true;
            case R.id.medium:
                selectedText.setTextSize(14);
                return true;
            case R.id.big:
                selectedText.setTextSize(18);
                return true;
            case R.id.red:
                selectedText.setTextColor(Color.RED);
                return true;
            case R.id.blue:
                selectedText.setTextColor(Color.BLUE);
                return true;
            case R.id.green:
                selectedText.setTextColor(Color.GREEN);
                return true;
            case R.id.cyan:
                selectedText.setBackgroundColor(Color.CYAN);
                return true;
            case R.id.magenta:
                selectedText.setBackgroundColor(Color.MAGENTA);
                return true;
            case R.id.yellow:
                selectedText.setBackgroundColor(Color.YELLOW);
                return true;
        }

        return super.onOptionsItemSelected(item);
    }
}