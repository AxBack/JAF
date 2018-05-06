package com.wallpaper.axb.view;

import android.content.Context;
import android.support.annotation.Nullable;
import android.support.annotation.StringRes;
import android.util.AttributeSet;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import com.wallpaper.axb.engine.R;

public class SliderItem extends LinearLayout implements SeekBar.OnSeekBarChangeListener {

    public interface OnValueChangedListener {
        void onValueChanged(int value);
    }

    private int mMin = 0;

    private OnValueChangedListener mListener = null;

    public SliderItem(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public SliderItem(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public SliderItem(Context context) {
        super(context);
    }

    public void setData(@StringRes int label, @StringRes int desc, int min, int max, int value, OnValueChangedListener listener) {

        mListener = listener;
        mMin = min;

        SeekBar seekBar = findViewById(R.id.seekBar);
        seekBar.setMax(max - min);
        seekBar.setProgress(value - min);
        seekBar.setOnSeekBarChangeListener(this);

        final TextView labelView = findViewById(R.id.label);
        labelView.setText(label);

        final TextView descView = ((TextView) findViewById(R.id.desc_text));
        descView.setText(desc);
        descView.setVisibility(GONE);

        setOnClickListener((View) -> descView.setVisibility(descView.getVisibility() == GONE ? VISIBLE : GONE));
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        mListener.onValueChanged(mMin + progress);
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) {

    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) {

    }
}
