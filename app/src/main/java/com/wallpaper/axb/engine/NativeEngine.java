package com.wallpaper.axb.engine;


import android.content.res.AssetManager;

class NativeEngine {

    public native int create(AssetManager assetManager);
    public native void destroy(int id);
    public native void reset(int id, String internalFile);
    public native boolean render(int id);
    public native void resume(int id);
    public native void pause(int id);
    public native void setSize(int id, int w, int h);
    public native void onTouch(int id, float x, float y);
    public native void onOffsetChanged(int id, float x, float y);
    public native void allowDeviation(int id, boolean allow);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-engine-lib");
    }
}
