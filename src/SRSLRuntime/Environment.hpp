#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include "../../include/SLDF_File.hpp"

namespace SrslRuntime{

    class Environment{
    public:
        explicit Environment(const std::string& dataFile);

        ~Environment();

    private:
        sldf::SLDF_File m_File;
    };

}