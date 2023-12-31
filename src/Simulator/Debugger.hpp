#pragma once

#include "Worker.hpp"
#include <filesystem>

namespace Simulator{

    class Debugger: public Worker{
    public:
        Debugger();

        ~Debugger() override;

    private:
        const std::filesystem::path m_GDBPath;
        FILE* m_GDB;
    };

}