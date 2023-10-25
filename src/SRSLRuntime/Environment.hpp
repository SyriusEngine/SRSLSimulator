#pragma once

#include <unordered_map>
#include <string>
#include <vector>

namespace SrslRuntime{

    class Environment{
    public:
        explicit Environment(const std::string& dataFile);

        ~Environment();
    };

}