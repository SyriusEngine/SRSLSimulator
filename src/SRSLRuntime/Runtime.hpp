#pragma once

#include "Environment.hpp"

namespace SrslRuntime{

    class Runtime{
    public:
        Runtime(const std::string& dataFile);

        ~Runtime();

        void execute();

    private:
        Environment* m_Environment;
    };

}