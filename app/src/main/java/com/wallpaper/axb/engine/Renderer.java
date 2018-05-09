package com.wallpaper.axb.engine;

import android.content.Context;
import android.content.SharedPreferences;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.content.Context.MODE_PRIVATE;

public class Renderer implements GLSurfaceView.Renderer, SharedPreferences.OnSharedPreferenceChangeListener {

    public static final String TILT_ENABLED = "TiltEnable";
    public static final String ROCKET_DEVIATION = "AllowRocketDeviation";
    public static final String BURST_DEVIATION = "AllowBurstDeviation";
    public static final String TRAIL_DEVIATION = "AllowTrailDeviation";
    public static final String NR_BURSTS = "NrBursts";
    public static final String MIN_NR_ROCKETS = "MinNrRockets";
    public static final String MAX_NR_ROCKETS = "MaxNrRockets";

    protected final Context mContext;
    protected final NativeEngine mRenderEngine = new NativeEngine();

    protected int mNativeId = -1;
    protected boolean mIsActive = false;

    public Renderer(Context ctx) {
        mContext = ctx;
    }

    @Override
    public void onSharedPreferenceChanged(SharedPreferences sharedPreferences, String key) {
        if(key.equals(TILT_ENABLED)) {
            boolean b = sharedPreferences.getBoolean(TILT_ENABLED, true);
            enableTilt(b);
        } else if(key.equals(ROCKET_DEVIATION)) {
            boolean b = sharedPreferences.getBoolean(ROCKET_DEVIATION, true);
            allowRocketDeviation(b);
        } else if(key.equals(BURST_DEVIATION)) {
            boolean b = sharedPreferences.getBoolean(BURST_DEVIATION, true);
            allowBurstDeviation(b);
        } else if(key.equals(TRAIL_DEVIATION)) {
            boolean b = sharedPreferences.getBoolean(TRAIL_DEVIATION, true);
            allowTrailDeviation(b);
        } else if(key.equals(NR_BURSTS)) {
            int n = sharedPreferences.getInt(NR_BURSTS, 3);
            setNrBursts(n);
        }else if(key.equals(MIN_NR_ROCKETS)) {
            int n = sharedPreferences.getInt(MIN_NR_ROCKETS, 1);
            setMinNrRockets(n);
        }
        else if(key.equals(MAX_NR_ROCKETS)) {
            int n = sharedPreferences.getInt(MAX_NR_ROCKETS, 6);
            setMaxNrRocketsPerSequence(n);
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

    public void enableTilt(boolean enable) {
        if(mNativeId >= 0)
            mRenderEngine.enableTilt(mNativeId, enable);
    }

    public void allowRocketDeviation(boolean allow) {
        if(mNativeId >= 0)
            mRenderEngine.allowRocketDeviation(mNativeId, allow);
    }

    public void allowBurstDeviation(boolean allow) {
        if(mNativeId >= 0)
            mRenderEngine.allowBurstDeviation(mNativeId, allow);
    }

    public void allowTrailDeviation(boolean allow) {
        if(mNativeId >= 0)
            mRenderEngine.allowTrailDeviation(mNativeId, allow);
    }

    public void setNrBursts(int nr) {
        if(mNativeId >= 0)
            mRenderEngine.setNrBursts(mNativeId, nr);
    }

    public void setMinNrRockets(int nr) {
        if(mNativeId >= 0)
            mRenderEngine.setMinNrRockets(mNativeId, nr);
    }

    public void setMaxNrRocketsPerSequence(int nr) {
        if(mNativeId >= 0)
            mRenderEngine.setMaxNrRocketsPerSequence(mNativeId, nr);
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
        boolean b = prefs.getBoolean(ROCKET_DEVIATION, true);
        allowRocketDeviation(b);

        b = prefs.getBoolean(BURST_DEVIATION, true);
        allowBurstDeviation(b);

        b = prefs.getBoolean(TRAIL_DEVIATION, true);
        allowTrailDeviation(b);

        int nr = prefs.getInt(NR_BURSTS, 3);
        setNrBursts(nr);

        nr = prefs.getInt(MIN_NR_ROCKETS, 1);
        setMinNrRockets(nr);

        nr = prefs.getInt(MAX_NR_ROCKETS, 6);
        setMaxNrRocketsPerSequence(nr);

        prefs.registerOnSharedPreferenceChangeListener(this);
    }
}
