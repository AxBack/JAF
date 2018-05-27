package com.axb.jaf;

import android.content.Context;
import android.support.annotation.ArrayRes;
import android.support.annotation.Nullable;
import android.support.annotation.StringRes;
import android.util.AttributeSet;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;

public class ComboBox extends LinearLayout {

    final Context mContext;

    public ComboBox(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
        mContext = context;
    }

    public ComboBox(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        mContext = context;
    }

    public ComboBox(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
    }

    public ComboBox(Context context) {
        super(context);
        mContext = context;
    }

    public void setData(@StringRes int label, @StringRes int desc, @ArrayRes int items, int index, Spinner.OnItemSelectedListener listener) {
        Spinner s = findViewById(R.id.spinner);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(mContext, android.R.layout.simple_spinner_item, mContext.getResources().getStringArray(items));
        adapter.setDropDownViewResource(R.layout.spinner_dropdown_item);
        s.setAdapter(adapter);
        s.setSelection(index);
        s.setOnItemSelectedListener(listener);

        final TextView labelView = findViewById(R.id.label);
        labelView.setText(label);

        final TextView descView = ((TextView) findViewById(R.id.desc_text));
        descView.setText(desc);
        descView.setVisibility(GONE);

        setOnClickListener((View) -> descView.setVisibility(descView.getVisibility() == GONE ? VISIBLE : GONE));
    }
}
