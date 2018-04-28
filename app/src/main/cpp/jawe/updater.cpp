#include "updater.h"
#include "counter.h"

#include <chrono>
#include <cmath>

namespace JAWE {

#define EPSILON 0.0001f

    UINT Updater::sThreadCounter = 0;

    bool Updater::init() {
        start();

        return true;
    }

    void Updater::start() {
        if (m_running)
            return;

        m_running = true;
        m_workThread = std::thread([=]() { this->run(); });
        LOGI("WorkerThread( Started: %d )", m_id);
    }

    void Updater::stop() {
        if (!m_running)
            return;

        m_running = false;

        if (m_workThread.joinable()) {
            try {
                m_workThread.join();
                LOGI("WorkerThread( Ended: %d )", m_id);
            }
            catch (...) {
                LOGE("WorkerThread( Failed to join: %d )", m_id);
            }
        }
    }

    void Updater::run() {
        Counter counter;

        while (true) {
            advance(counter.step());
            if (!m_running)
                break;
        }
    }
}
