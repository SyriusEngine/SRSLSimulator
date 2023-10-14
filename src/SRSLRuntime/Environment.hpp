#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include "../../Execute/Basic-vs.hpp"

namespace SrslRuntime{

    struct InterfaceDataDesc{
        void* data = nullptr;
        size_t size = 0; // size of the array in bytes (essentially multiple vertices)
        size_t stride = 0; // size of a single element in bytes (essentially a single vertex)
    };

    class Environment{
    public:
        Environment();

        void execute(const InterfaceDataDesc& inputData, InterfaceDataDesc& outputData);

    private:

    };

}