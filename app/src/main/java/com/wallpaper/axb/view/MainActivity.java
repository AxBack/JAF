package com.wallpaper.axb.view;

import android.app.Activity;
import android.app.WallpaperManager;
import android.content.ComponentName;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.LinearLayout;

import com.wallpaper.axb.engine.R;
import com.wallpaper.axb.engine.WallpaperService;

/**
 * The main activity for this app.
 */
public class MainActivity extends Activity {

    /**
     * {@inheritDoc}
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final LinearLayout main = findViewById(R.id.main);

        Button btn = findViewById(R.id.setBtn);
        btn.setOnClickListener((View v) -> setAsWallpaper());

        View v = LayoutInflater.from(this).inflate(R.layout.check_box_item, main);
        final CheckBoxItem deviation = v.findViewById(R.id.check_box_item);
        deviation.setData(R.string.allow_deviation_text, R.string.deviation_desc, true, (CompoundButton b, boolean checked) -> {
            updatePrefs("AllowDeviation", checked);
        });
    }

    private void updatePrefs(String key, boolean value) {
        SharedPreferences.Editor editor = this.getSharedPreferences("JAF", MODE_PRIVATE).edit();
        editor.putBoolean(key, value);
        editor.apply();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if ( requestCode == 123 && resultCode == RESULT_OK) {

        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    /**
     * {@inheritDoc}
     */
    @Override
    protected void onPause() {
        super.onPause();
    }

    /**
     * {@inheritDoc}
     */
    @Override
    protected void onResume() {
        super.onResume();
    }

    /**
     * Request to set this LWP through Android wallpaper picker.
     */
    private void setAsWallpaper() {
        Intent intent = new Intent(
                WallpaperManager.ACTION_CHANGE_LIVE_WALLPAPER)
                .putExtra(WallpaperManager.EXTRA_LIVE_WALLPAPER_COMPONENT,
                        new ComponentName(this, WallpaperService.class));
        startActivityForResult(intent, 123);
    }
}
