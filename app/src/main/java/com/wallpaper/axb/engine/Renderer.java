package com.wallpaper.axb.engine;

import android.content.Context;
import android.content.SharedPreferences;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.content.Context.MODE_PRIVATE;

class Renderer implements GLSurfaceView.Renderer, SharedPreferences.OnSharedPreferenceChangeListener {

    protected final Context mContext;
    protected final NativeEngine mRenderEngine = new NativeEngine();

    protected int mNativeId = -1;
    protected boolean mIsActive = false;

    public Renderer(Context ctx) {
        mContext = ctx;
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
        if(key.equals("AllowDeviation")) {
            boolean b = sharedPreferences.getBoolean("AllowDeviation", true);
            allowDeviation(b);
        }
    }

    public synchronized void reset(String binaryFile) {
        if(mNativeId >= 0)
            mRenderEngine.reset(mNativeId, mContext.getFilesDir().getAbsolutePath() + "/" + binaryFile);
    }

    public synchronized void destroy() {
        if(mNativeId >= 0)
            mRenderEngine.destroy(mNativeId);
        mNativeId = -1;

        SharedPreferences prefs = mContext.getSharedPreferences("JAF", MODE_PRIVATE);
        prefs.unregisterOnSharedPreferenceChangeListener(this);
    }

    @Override
    public synchronized void onSurfaceCreated(GL10 gl, EGLConfig config) {
        createEngine();
    }

    @Override
    public synchronized void onSurfaceChanged(GL10 gl, int width, int height) {
        if(mNativeId >= 0)
            mRenderEngine.setSize(mNativeId, width,height);
    }

    @Override
    public synchronized void onDrawFrame(GL10 gl) {
        if(mNativeId >= 0)
            mRenderEngine.render(mNativeId);
    }

    public void onOffsetChanged(float xOffset, float yOffset) {
        if (mNativeId >= 0)
            mRenderEngine.onOffsetChanged(mNativeId, xOffset, yOffset);
    }

    public void resume() {
        if(!mIsActive) {
            mIsActive = true;
            if(mNativeId >= 0)
                mRenderEngine.resume(mNativeId);
        }
    }

    public void pause() {
        if(mIsActive) {
            mIsActive = false;
            if(mNativeId >= 0)
                mRenderEngine.pause(mNativeId);
        }
    }

    public void allowDeviation(boolean allow) {
        if(mNativeId >= 0)
            mRenderEngine.allowDeviation(mNativeId, allow);
    }

    public void onTouch(float x, float y) {
        if(mNativeId >= 0) {
            mRenderEngine.onTouch(mNativeId,x,y);
        }
    }

    public void onPinch(float diff) {

    }

    private synchronized void createEngine() {
        if(mNativeId > -1)
            return;

        mNativeId = mRenderEngine.create(mContext.getAssets());
        if(mIsActive)
            mRenderEngine.resume(mNativeId);

        SharedPreferences prefs = mContext.getSharedPreferences("JAF", MODE_PRIVATE);
        boolean b = prefs.getBoolean("AllowDeviation", true);
        allowDeviation(b);

        prefs.registerOnSharedPreferenceChangeListener(this);
    }
}
