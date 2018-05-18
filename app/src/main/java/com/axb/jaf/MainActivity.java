package com.axb.jaf;

import android.app.Activity;
import android.app.WallpaperManager;
import android.content.ComponentName;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.annotation.StringRes;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.Toast;

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

        setupCheckBox(main, R.string.immersive_label, R.string.immersive_desc, Renderer.IMMERSIVE_MODE, true);
        setupCheckBox(main, R.string.interactive_label, R.string.interactive_desc, Renderer.INTERACTIVE_MODE, true);
        setupCheckBox(main, R.string.allow_rocket_deviation_label, R.string.rocket_deviation_desc, Renderer.ROCKET_DEVIATION, true);
        setupCheckBox(main, R.string.allow_burst_deviation_label, R.string.burst_deviation_desc, Renderer.BURST_DEVIATION, true);
        setupCheckBox(main, R.string.allow_trail_deviation_label, R.string.trail_deviation_desc, Renderer.TRAIL_DEVIATION, true);

        setupSlider(main, R.string.nr_bursts_label, R.string.nr_burst_desc, 1, 5, 3, Renderer.NR_BURSTS);
        setupSlider(main, R.string.min_number_rockets_label, R.string.min_number_rockets_desc, 1, 10, 3, Renderer.MIN_NR_ROCKETS);
        setupSlider(main, R.string.max_number_rockets_label, R.string.max_number_rockets_desc, 1, 9, 4, Renderer.MAX_NR_ROCKETS);

    }

    private void setupCheckBox(LinearLayout main, @StringRes int label, @StringRes int desc, String key, boolean def) {
        SharedPreferences prefs = getPrefs();
        boolean state = prefs.getBoolean(key, def);

        View v = LayoutInflater.from(this).inflate(R.layout.check_box_item, main, false);
        final CheckBoxItem item = v.findViewById(R.id.check_box_item);
        item.setData(label, desc, state, (CompoundButton b, boolean checked) -> updatePrefs(key, checked) );
        main.addView(v);
    }

    private void setupSlider(LinearLayout main, @StringRes int label, @StringRes int desc, int min, int max, int def, String key) {
        SharedPreferences prefs = getPrefs();
        int curr = prefs.getInt(key, def);

        View v = LayoutInflater.from(this).inflate(R.layout.slider_item, main, false);
        final SliderItem item = v.findViewById(R.id.slider_item);
        item.setData(label, desc, min, max, curr, (int value) -> {
                updatePrefs(key, value);
                Toast.makeText(MainActivity.this, Integer.toString(value), Toast.LENGTH_SHORT).show();
        });
        main.addView(v);
    }

    private SharedPreferences getPrefs() {
        return this.getSharedPreferences("JAF", MODE_PRIVATE);
    }

    private void updatePrefs(String key, boolean value) {
        SharedPreferences.Editor editor = getPrefs().edit();
        editor.putBoolean(key, value);
        editor.apply();
    }

    private void updatePrefs(String key, int value) {
        SharedPreferences.Editor editor = getPrefs().edit();
        editor.putInt(key, value);
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