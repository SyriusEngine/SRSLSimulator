#pragma once

#include "Worker.hpp"
#include <filesystem>
#include <processthreadsapi.h>
#include <windows.h>

namespace Simulator{

    class Debugger: public Worker{
    public:
        Debugger();

        ~Debugger() override;

        void sendCommand(std::string command);

    private:
        const std::filesystem::path m_GDBPath;

        HANDLE m_GDBProcess;
        HANDLE m_GDBThread;
        uint32_t m_GDBProcessID;
        uint32_t m_GDBThreadID;

        HANDLE hChildStd_IN_Rd;
        HANDLE hChildStd_IN_Wr; // Write handle for the child process's STDIN.
        HANDLE hChildStd_OUT_Rd; // Read handle for the child process's STDOUT.
        HANDLE hChildStd_OUT_Wr;

    };

}