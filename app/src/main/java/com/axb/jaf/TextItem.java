package com.axb.jaf;

import android.content.Context;
import android.support.annotation.Nullable;
import android.support.annotation.StringRes;
import android.util.AttributeSet;
import android.widget.LinearLayout;
import android.widget.TextView;

public class TextItem extends LinearLayout {

    public TextItem(Context context) {
        super(context);
    }

    public TextItem(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public TextItem(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public TextItem(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }

    public void setData(@StringRes int label, @StringRes int desc) {
        final TextView labelView = findViewById(R.id.label);
        labelView.setText(label);

        final TextView descView = ((TextView) findViewById(R.id.desc_text));
        descView.setText(desc);
        descView.setVisibility(GONE);

        setOnClickListener((View) -> descView.setVisibility(descView.getVisibility() == GONE ? VISIBLE : GONE));
    }
}
