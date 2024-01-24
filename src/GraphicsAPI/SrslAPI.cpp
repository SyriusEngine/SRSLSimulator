#include "../../include/GraphicsAPI/SrslAPI.hpp"
#include "../../include/GraphicsAPI/Profiler.hpp"
#include "Impl/ContextImpl.hpp"

namespace SrslAPI{

    UP<Context> createContext(){
        return createUP<ContextImpl>();
    }

    const std::unordered_map<std::string, uint64_t> &getTimingData(){
        return Timers::getDurations();
    }

    void startTimer(const std::string &name){
        Timers::startTimer(name);
    }

    void stopTimer(const std::string &name){
        Timers::stopTimer(name);
    }

}
