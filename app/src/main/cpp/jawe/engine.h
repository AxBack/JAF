#pragma once

#include <android/asset_manager_jni.h>

#include <vector>
#include "matrix.h"
#include "../pch.h"

#include "updater.h"
#include "mesh.h"

namespace JAWE {

    class Engine {
    protected:

        static UINT sThreadCounter;

        UINT m_id { sThreadCounter++ };

        GLint m_viewport[4] { 0,0,0,0 };

    public:

        Engine() {
        }

        virtual ~Engine() {
            clear();
        }

        virtual void clear() {};

        virtual bool init(AAssetManager *pAssetManager) = 0;

        virtual bool render() = 0;

        virtual void resume() = 0;

        virtual void pause() = 0;

        virtual void updateSize(int width, int height)
        {
            LOGI("engine(size updated: %d, %d )", width, height);
            m_viewport[0] = m_viewport[1] = 0;
            m_viewport[2] = width;
            m_viewport[3] = height;
        }

        virtual void touch(float /*x*/, float /*y*/) {}
        virtual void doubleTap(float /*x*/, float /*y*/) {}
        virtual void pinch(float /*diff*/) {}
		virtual void rotate(float /*angle*/) {}
        virtual void setOffset(float /*x*/, float /*y*/) {}
    };
}
