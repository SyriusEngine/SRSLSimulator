#include "Debugger.hpp"
#include <iostream>

namespace Simulator{

    Debugger::Debugger():
    Worker(),
    m_GDBPath(R"(C:\Program Files\JetBrains\CLion 2022.3\bin\gdb\win\bin\gdb.exe)"){
        if (!std::filesystem::exists(m_GDBPath)){
            std::cerr << "GDB not found: " << m_GDBPath << std::endl;
            return;
        }

        auto thisPid = GetCurrentProcessId();

        addTask([this, thisPid]{
            std::stringstream cmd;
            cmd << m_GDBPath << " -p " << thisPid;
            printf("cmd: %s\n", cmd.str().c_str());

            SECURITY_ATTRIBUTES saAttr;
            saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
            saAttr.bInheritHandle = TRUE;
            saAttr.lpSecurityDescriptor = NULL;

            // Create pipes for GDB process
            CreatePipe(&hChildStd_OUT_Rd, &hChildStd_OUT_Wr, &saAttr, 0);
            CreatePipe(&hChildStd_IN_Rd, &hChildStd_IN_Wr, &saAttr, 0);

            STARTUPINFO si;
            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);
            si.dwFlags |= STARTF_USESTDHANDLES;
            si.hStdInput = hChildStd_IN_Rd;
            si.hStdOutput = hChildStd_OUT_Wr;
            si.hStdError = hChildStd_OUT_Wr;

            PROCESS_INFORMATION pi;
            ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

            if (!CreateProcessA(
                    nullptr,
                    const_cast<char*>(cmd.str().c_str()),
                    nullptr,
                    nullptr,
                    TRUE,
                    0,
                    nullptr,
                    nullptr,
                    &si,
                    &pi
            )){
                printf("CreateProcess failed (%lu).\n", GetLastError());
                return;
            }
            else{
                m_GDBProcess = pi.hProcess;
                m_GDBThread = pi.hThread;
                m_GDBProcessID = pi.dwProcessId;
                m_GDBThreadID = pi.dwThreadId;

                CloseHandle(hChildStd_IN_Rd);
                CloseHandle(hChildStd_OUT_Wr);

                printf("Attached GDB (with process ID: %u) to process %lu.\n", m_GDBProcessID, thisPid);

                const unsigned int bufferSize = 4096;
                char buffer[bufferSize];
                DWORD dwRead = 1;
                while (ReadFile(hChildStd_OUT_Rd, buffer, bufferSize - 1, &dwRead, nullptr) && dwRead > 0){
                    buffer[dwRead] = '\0';
                    printf("GDB response: %s\n", buffer);
                }
            }
        });
    }

    Debugger::~Debugger() {
        if (m_GDBProcess != nullptr){
            TerminateProcess(m_GDBProcess, 0);
            CloseHandle(m_GDBProcess);
            CloseHandle(m_GDBThread);
        }
    }

    void Debugger::sendCommand(std::string command) {
        addTask([this, command]{
            // send command to GDB
            DWORD dwWritten = 0;
            WriteFile(hChildStd_IN_Wr, command.c_str(), command.size(), &dwWritten, nullptr);

            // read response from GDB
            DWORD dwRead = 0;
            char buffer[1024];
            ReadFile(hChildStd_OUT_Rd, buffer, 1023, &dwRead, nullptr);
            buffer[dwRead] = '\0';
            printf("GDB response: %s\n", buffer);

        });

    }
}
