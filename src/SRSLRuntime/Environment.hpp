#pragma once

#include <unordered_map>
#include <string>
#include "../../Execute/Basic-vs.hpp"
#include "../../Execute/Basic-fs.hpp"

namespace SrslRuntime{

    struct InterfaceDataDesc{
        void* data;
        size_t size; // size of the array in bytes (essentially multiple vertices)
        size_t stride; // size of a single element in bytes (essentially a single vertex)
    };

    class Environment{
    public:
        Environment();

    private:



    };

}