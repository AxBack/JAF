package com.axb.jaf;

import android.content.Context;
import android.support.annotation.Nullable;
import android.support.annotation.StringRes;
import android.util.AttributeSet;
import android.widget.LinearLayout;
import android.widget.Switch;
import android.widget.TextView;

public class CheckBoxItem extends LinearLayout {

    public CheckBoxItem(Context context) {
        super(context);
    }

    public CheckBoxItem(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public CheckBoxItem(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public CheckBoxItem(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }

    public void setData(@StringRes int label, @StringRes int desc, boolean checked, Switch.OnCheckedChangeListener listener) {
        Switch s = findViewById(R.id.switchbox);
        s.setChecked(checked);
        s.setOnCheckedChangeListener(listener);

        final TextView labelView = findViewById(R.id.label);
        labelView.setText(label);

        final TextView descView = ((TextView) findViewById(R.id.desc_text));
        descView.setText(desc);
        descView.setVisibility(GONE);

        setOnClickListener((View) -> descView.setVisibility(descView.getVisibility() == GONE ? VISIBLE : GONE));
    }
}
