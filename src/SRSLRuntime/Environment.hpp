#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

namespace SrslRuntime{

    class Environment{
    public:
        explicit Environment(const std::string& dataFile);

        ~Environment();
    };

}