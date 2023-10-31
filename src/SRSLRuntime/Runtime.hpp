#pragma once

#include "Environment.hpp"
#include "Shader/comp-vs.hpp"
#include "Shader/comp-fs.hpp"

namespace SrslRuntime{

    class Runtime{
    public:
        explicit Runtime(const std::string& dataFile);

        ~Runtime();

        void execute();

    private:

        void vertexShaderStage();

        void rasterizerStage();

    private:
        Environment* m_Environment;
        std::vector<Vertex_OUTPUT> m_Vertices;
    };

}