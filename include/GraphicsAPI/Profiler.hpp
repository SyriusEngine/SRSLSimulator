#pragma once

#include "../../src/Simulator/SimulatorInclude.hpp"

namespace SrslAPI {

    class SRSL_GRAPHICS_API Timers {
    public:

        static void startTimer(const std::string &name);

        static void stopTimer(const std::string &name);

        static const std::unordered_map<std::string, uint64_t> &getDurations() {
            return m_Durations;
        }

    private:
        static std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>> m_StartTimes;
        static std::unordered_map<std::string, uint64_t> m_Durations;
    };

}

#define SIM_START_TIME(name) SrslAPI::Timers::startTimer(name);
#define SIM_STOP_TIME(name) SrslAPI::Timers::stopTimer(name);