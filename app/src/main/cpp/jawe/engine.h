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

		AAssetManager* m_pAssetManager;
		std::atomic_bool m_initialized { false };

		std::mutex m_mutex;

	protected:

		virtual bool onInit(AAssetManager* pAssetManager) = 0;
		virtual bool onRender() = 0;
		virtual void onResume() = 0;
		virtual void onPause() = 0;

		virtual void onTouch(float /*x*/, float /*y*/) {}
		virtual void onTap(float /*x*/, float /*y*/) {}
		virtual void onDoubleTap(float /*x*/, float /*y*/) {}
		virtual void onPinch(float /*diff*/) {}
		virtual void onOffset(float /*x*/, float /*y*/) {}

    public:

        Engine() {
        }

        virtual ~Engine() {
            clear();
        }

        void clear() {}

        bool init(AAssetManager *pAssetManager)
        {
			m_pAssetManager = pAssetManager;
			m_initialized = false;
			return true;
        }

        bool render()
        {
			if(!m_initialized && m_pAssetManager)
				m_initialized = onInit(m_pAssetManager);

			std::lock_guard<std::mutex> _(m_mutex);
			return m_initialized && onRender();
        }

        void resume()
        {
			std::lock_guard<std::mutex> _(m_mutex);
			if(m_initialized)
				onResume();
        }

        void pause()
        {
			std::lock_guard<std::mutex> _(m_mutex);
			if(m_initialized)
				onPause();
        }

        virtual void updateSize(int width, int height)
        {
			std::lock_guard<std::mutex> _(m_mutex);
            LOGI("engine(size updated: %d, %d )", width, height);
            m_viewport[0] = m_viewport[1] = 0;
            m_viewport[2] = width;
            m_viewport[3] = height;
        }

        void touch(float x, float y)
		{
			if(!m_initialized)
				return;
			std::lock_guard<std::mutex> _(m_mutex);
			onTouch(x,y);
		}

		void tap(float x, float y)
		{
			if(!m_initialized)
				return;
			std::lock_guard<std::mutex> _(m_mutex);
			onTap(x,y);
		}

        void doubleTap(float x, float y)
		{
			if(!m_initialized)
				return;
			std::lock_guard<std::mutex> _(m_mutex);
			onDoubleTap(x,y);
		}

        void pinch(float diff)
		{
			if(!m_initialized)
				return;
			std::lock_guard<std::mutex> _(m_mutex);
			onPinch(diff);
		}

        void setOffset(float x, float y)
		{
			if(!m_initialized)
				return;
			std::lock_guard<std::mutex> _(m_mutex);
			onOffset(x,y);
		}
    };
}
