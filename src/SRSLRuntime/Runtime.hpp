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

        void primitiveAssemblyStage();

        void rasterizerStage();

    private:
        Environment* m_Environment;
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
    };

}