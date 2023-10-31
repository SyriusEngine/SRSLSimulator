#pragma once

#include "Environment.hpp"
#include "Shader/comp-vs.hpp"
#include "Shader/comp-fs.hpp"

namespace SrslRuntime{

    class Runtime{
    public:
        Runtime(const std::string& dataFile);

        ~Runtime();

        void execute();

    private:

        std::vector<Vertex_OUTPUT> vertexShaderStage();

    private:
        Environment* m_Environment;
    };

}