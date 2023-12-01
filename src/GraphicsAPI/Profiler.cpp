#include "GraphicsAPI/Profiler.hpp"

namespace SrslAPI {

    std::unordered_map<std::string, std::chrono::time_point<std::chrono::high_resolution_clock>> Timers::m_StartTimes;
    std::unordered_map<std::string, uint64_t> Timers::m_Durations;


    void Timers::startTimer(const std::string &name) {
        m_StartTimes[name] = std::chrono::high_resolution_clock::now();
    }

    void Timers::stopTimer(const std::string &name) {
        auto end = std::chrono::high_resolution_clock::now();
        m_Durations[name] = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_StartTimes[name]).count();
    }

}