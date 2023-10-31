#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include "../../include/SLDF_File.hpp"
#include "Primitives.hpp"

namespace SrslRuntime{

    class Environment{
    public:
        explicit Environment(const std::string& dataFile);

        ~Environment();

    public:
        sldf::SLDF_File m_SLDFFile;

    private:
    };

}