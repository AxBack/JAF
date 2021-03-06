#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <atomic>
#include "../pch.h"

namespace JAWE {

    class Updater {
    private:

        static UINT sThreadCounter;

        UINT m_id { 0 };

        std::atomic_bool m_running;
        std::thread m_workThread;

	protected:
        void start();

        void stop();

        void run();

        virtual void advance(float dt) = 0;

    public:

        Updater()
                : m_running(false) {
            m_id = sThreadCounter;
            ++sThreadCounter;
            _logi("engine( Created: %d )", m_id);
        }

        virtual ~Updater() {
            stop();
        }

        virtual bool init();

        void resume() {
            start();
        }

        void pause() {
            stop();
        }

		bool isRunning() { return m_running; }
    };
}