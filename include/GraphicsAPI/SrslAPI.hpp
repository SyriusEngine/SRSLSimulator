#pragma once

#include "Include.hpp"
#include "Context.hpp"

namespace SrslAPI{

    SRSL_GRAPHICS_API UP<Context> createContext();

    SRSL_GRAPHICS_API const std::unordered_map<std::string, uint64_t> &getTimingData();

    SRSL_GRAPHICS_API void startTimer(const std::string &name);

    SRSL_GRAPHICS_API void stopTimer(const std::string &name);



}