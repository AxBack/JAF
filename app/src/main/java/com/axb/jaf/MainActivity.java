package com.axb.jaf;

import android.app.Activity;
import android.app.WallpaperManager;
import android.content.ComponentName;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.annotation.ArrayRes;
import android.support.annotation.StringRes;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.Toast;

import java.util.Random;

/**
 * The main activity for this app.
 */
public class MainActivity extends Activity {

    private static final int[] BANNERS = {
            R.drawable.banner_0, R.drawable.banner_1, R.drawable.banner_2,
            R.drawable.banner_3, R.drawable.banner_4, R.drawable.banner_5,
            R.drawable.banner_6
    };

    Toast mToast = null;

    /**
     * {@inheritDoc}
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ImageView image = findViewById(R.id.imageView);
        image.setImageResource(BANNERS[(new Random()).nextInt(7)]);

        final LinearLayout main = findViewById(R.id.main);

        Button btn = findViewById(R.id.setBtn);
        btn.setOnClickListener((View v) -> setAsWallpaper());

        setupComboBox(main ,R.string.interactive_label, R.string.interactive_desc, R.array.interactable_options, Renderer.INTERACTIVE_MODE, 2);
        //setupCheckBox(main, R.string.interactive_label, R.string.interactive_desc, Renderer.INTERACTIVE_MODE, true);
        setupCheckBox(main, R.string.immersive_label, R.string.immersive_desc, Renderer.IMMERSIVE_MODE, true);
        setupCheckBox(main, R.string.allow_rocket_deviation_label, R.string.rocket_deviation_desc, Renderer.ROCKET_DEVIATION, true);
        setupCheckBox(main, R.string.allow_burst_deviation_label, R.string.burst_deviation_desc, Renderer.BURST_DEVIATION, true);
        setupCheckBox(main, R.string.allow_trail_deviation_label, R.string.trail_deviation_desc, Renderer.TRAIL_DEVIATION, true);

        setupSlider(main, R.string.nr_bursts_label, R.string.nr_burst_desc, 1, 5, 3, Renderer.NR_BURSTS, true);
        setupSlider(main, R.string.min_number_rockets_label, R.string.min_number_rockets_desc, 1, 10, 3, Renderer.MIN_NR_ROCKETS, true);
        setupSlider(main, R.string.max_number_rockets_label, R.string.max_number_rockets_desc, 1, 9, 4, Renderer.MAX_NR_ROCKETS, true);
        setupSlider(main, R.string.rotation_label, R.string.rotation_desc, 0, 360, 180, Renderer.ROTATION_SPAN, true);
        setupSlider(main, R.string.delta_factor_label, R.string.delta_factor_desc, 0, 2, 1, Renderer.DELTA_FACTOR, false);

        setupText(main, R.string.special_thanks_label, R.string.special_thanks_text);
    }

    private void showToast(String msg ) {
        if(mToast != null)
            mToast.cancel();

        mToast = Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT);
        mToast.show();
    }

    private void setupCheckBox(LinearLayout main, @StringRes int label, @StringRes int desc, String key, boolean def) {
        SharedPreferences prefs = getPrefs();
        boolean state = prefs.getBoolean(key, def);

        View v = LayoutInflater.from(this).inflate(R.layout.check_box_item, main, false);
        final CheckBoxItem item = v.findViewById(R.id.check_box_item);
        item.setData(label, desc, state, (CompoundButton b, boolean checked) -> updatePrefs(key, checked) );
        main.addView(v);
    }

    private void setupComboBox(LinearLayout main, @StringRes int label, @StringRes int desc, @ArrayRes int array, String key, int def) {
        SharedPreferences prefs = getPrefs();
        int state = prefs.getInt(key, def);

        View v = LayoutInflater.from(this).inflate(R.layout.combobox_item, main, false);
        final ComboBox item = v.findViewById(R.id.combo_box_item);
        item.setData(label, desc, array, state, new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                updatePrefs(key, position);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
        main.addView(v);
    }

    private void setupSlider(LinearLayout main, @StringRes int label, @StringRes int desc, int min, int max, int def, String key, boolean showToast) {
        SharedPreferences prefs = getPrefs();
        int curr = prefs.getInt(key, def);

        View v = LayoutInflater.from(this).inflate(R.layout.slider_item, main, false);
        final SliderItem item = v.findViewById(R.id.slider_item);
        item.setData(label, desc, min, max, curr, (int value) -> {
                updatePrefs(key, value);
                if(showToast)
                    showToast(Integer.toString(value));
        });
        main.addView(v);
    }

    private void setupText(LinearLayout main, @StringRes int label, @StringRes int desc) {
        View v = LayoutInflater.from(this).inflate(R.layout.text_item, main, false);
        final TextItem item = v.findViewById(R.id.text_item);
        item.setData(label, desc);
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
