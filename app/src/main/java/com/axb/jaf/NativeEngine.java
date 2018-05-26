package com.axb.jaf;

import android.content.res.AssetManager;

class NativeEngine {

    public native int create(AssetManager assetManager);
    public native void destroy(int id);
    public native void reset(int id, String internalFile);
    public native boolean render(int id);
    public native void resume(int id);
    public native void pause(int id);
    public native void immersiveMode(int id, boolean enable);
    public native void interactive(int id, boolean enable);
    public native void allowRocketDeviation(int id, boolean allow);
    public native void allowBurstDeviation(int id, boolean allow);
    public native void allowTrailDeviation(int id, boolean allow);
    public native void setNrBursts(int id, int nr);
    public native void setMinNrRockets(int id, int nr);
    public native void setMaxNrRocketsPerSequence(int id, int nr);
    public native void setRotationSpan(int id, int nr);
    public native void setDeltaFactor(int id, float factor);

    public native void setSize(int id, int w, int h);
    public native void onTouch(int id, float x, float y);
    public native void onDoubleTap(int id, float x, float y);
    public native void onOffsetChanged(int id, float x, float y);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-engine-lib");
    }
}
