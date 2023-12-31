#include "Debugger.hpp"
#include <iostream>
#include <processthreadsapi.h>

namespace Simulator{

    Debugger::Debugger():
    Worker(),
    m_GDBPath(R"(C:\Program Files\JetBrains\CLion 2022.3\bin\gdb\win\bin\gdb.exe)"),
    m_GDB(nullptr){
        if (!std::filesystem::exists(m_GDBPath)){
            std::cerr << "GDB not found: " << m_GDBPath << std::endl;
            return;
        }
        auto thisPid = GetCurrentProcessId();
        addTask([this, thisPid]{
            std::stringstream cmd;
            cmd << m_GDBPath << " -p " << thisPid;
            m_GDB = _popen(cmd.str().c_str(), "r+");
            if (!m_GDB){
                std::cerr << "Failed to open GDB" << std::endl;
                return;
            }
        });
    }

    Debugger::~Debugger() {
        if (m_GDB){
            // close gdb
            addTask([this]{
                fprintf(m_GDB, "quit\n");
                fflush(m_GDB);
                fclose(m_GDB);
            });
        }
    }
}
