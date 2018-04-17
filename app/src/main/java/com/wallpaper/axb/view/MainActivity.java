package com.wallpaper.axb.view;

import android.app.Activity;
import android.app.WallpaperManager;
import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.wallpaper.axb.engine.R;
import com.wallpaper.axb.engine.WallpaperService;

/**
 * The main activity for this app.
 */
public class MainActivity extends Activity {

    // TODO: this should probably be bounded by a ServiceConnection.
    public static WallpaperService sWallpaperService;

    /**
     * {@inheritDoc}
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btn = findViewById(R.id.setBtn);
        btn.setOnClickListener((View v) -> setAsWallpaper());
    }

    /**
     * {@inheritDoc}
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (sWallpaperService != null && requestCode == 123 && resultCode == RESULT_OK) {
            sWallpaperService.restart();
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

    private String getWallpaperFilePath() {
        return this.getFilesDir().getAbsolutePath() + "/WAE.dat";
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
