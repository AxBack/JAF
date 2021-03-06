package com.axb.jaf;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.support.v4.view.GestureDetectorCompat;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.SurfaceHolder;

public class WallpaperService extends android.service.wallpaper.WallpaperService {

    private static final boolean DEBUG = true;

    private Engine mEngine;

    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public android.service.wallpaper.WallpaperService.Engine onCreateEngine() {
        mEngine = new Engine();
        return mEngine;
    }

    private class Engine extends android.service.wallpaper.WallpaperService.Engine {

        private WallpaperView mSurfaceView;

        private float mTouchX = 0;
        private float mTouchY = 0;

        @Override
        public void onCreate(SurfaceHolder surfaceHolder) {
            super.onCreate(surfaceHolder);

            mSurfaceView = new WallpaperView(WallpaperService.this);
        }

        public void restart() {
            mSurfaceView.reset();
        }

        @Override
        public void onDestroy() {
            super.onDestroy();
            mSurfaceView.onDestroy();
            mSurfaceView = null;
        }

        @Override
        public void onSurfaceRedrawNeeded(SurfaceHolder holder) {
            mSurfaceView.requestRender();
            super.onSurfaceRedrawNeeded(holder);
        }

        @Override
        public void onTouchEvent(MotionEvent event) {
            mSurfaceView.onTouchEvent(event);
        }

        @Override
        public void onVisibilityChanged(boolean visible) {
            super.onVisibilityChanged(visible);

            if (mSurfaceView != null) {
                if (visible)
                    mSurfaceView.onResume();
                else
                    mSurfaceView.onPause();
            }
        }

        @Override
        public void onOffsetsChanged(float xOffset, float yOffset, float xOffsetStep, float yOffsetStep, int xPixelOffset, int yPixelOffset) {
            super.onOffsetsChanged(xOffset, yOffset, xOffsetStep, yOffsetStep, xPixelOffset, yPixelOffset);
            mSurfaceView.onOffsetsChanged(xOffset, yOffset);
        }

        private class WallpaperView extends GLSurfaceView
        {

            private com.axb.jaf.Renderer mRenderer;

            private final ScaleGestureDetector mScaleGestureDetector;
            private final GestureDetectorCompat mGestureDetector;
            private GestureHandler mGestureHandler;

            public WallpaperView(Context context) {
                super(context);
                setEGLConfigChooser(8, 8, 8, 8, 24, 1);
                setEGLContextClientVersion(3);
                setPreserveEGLContextOnPause(true);

                if(DEBUG) {
                    setDebugFlags(GLSurfaceView.DEBUG_CHECK_GL_ERROR);
                }

                mRenderer = new com.axb.jaf.Renderer(WallpaperService.this);
                setRenderer(mRenderer);
                setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);

                mGestureHandler = new GestureHandler();
                mScaleGestureDetector = new ScaleGestureDetector(WallpaperService.this, mGestureHandler);
                mGestureDetector = new GestureDetectorCompat(WallpaperService.this, mGestureHandler);
            }

            public void reset() {
                mRenderer.reset("WAE.dat");
            }

            @Override
            public void surfaceCreated(SurfaceHolder holder) {
                super.surfaceCreated(holder);
            }

            @Override
            public void onResume() {
                super.onResume();
                mRenderer.resume();
            }

            @Override
            public void onPause() {
                super.onPause();
                mRenderer.pause();
            }

            @Override
            public SurfaceHolder getHolder() {
                return getSurfaceHolder();
            }

            public void onDestroy() {
                super.onDetachedFromWindow();

                mRenderer.destroy();
                mRenderer = null;
            }


            @Override
            public boolean onTouchEvent(MotionEvent event) {

                mScaleGestureDetector.onTouchEvent(event);
                mGestureDetector.onTouchEvent(event);
                //mRotationDetector.onTouchEvent(event);

                final float x = event.getX();
                final float y = event.getY();

                if (x != mTouchX || y != mTouchY) {
                    mTouchX = x;
                    mTouchY = y;

                    if (event.getAction() == MotionEvent.ACTION_DOWN
                            || event.getAction() == MotionEvent.ACTION_MOVE) {
                        mSurfaceView.queueEvent(() -> mRenderer.onTouch(x,y));
                    }
                }
                return super.onTouchEvent(event);
            }

            public void onOffsetsChanged(float xOffset, float yOffset) {
                mRenderer.onOffsetChanged(xOffset, yOffset);
            }

            class GestureHandler extends GestureDetector.SimpleOnGestureListener implements ScaleGestureDetector.OnScaleGestureListener{

                @Override
                public boolean onScaleBegin(ScaleGestureDetector scaleGestureDetector) {
                    return true;
                }

                @Override
                public void onScaleEnd(ScaleGestureDetector scaleGestureDetector) {
                }

                @Override
                public boolean onScale(ScaleGestureDetector scaleGestureDetector) {
                    float diff = 1.0f - scaleGestureDetector.getScaleFactor();
                    if(diff != 0.0f)
                        mRenderer.onPinch(diff);
                    return true;
                }

                @Override
                public boolean onDoubleTap(MotionEvent e) {
                    mRenderer.onDoubleTap(e.getX(), e.getY());
                    return super.onDoubleTap(e);
                }

                @Override
                public boolean onSingleTapUp(MotionEvent e) {
                    mRenderer.onTap(e.getX(), e.getY());
                    return super.onSingleTapUp(e);
                }
            }
        }
    }
}
