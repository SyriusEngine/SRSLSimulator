#pragma once

#include "Environment.hpp"
#include "RenderTarget.hpp"
#include "Shader/comp-vs.hpp"
#include "Shader/comp-fs.hpp"

namespace SrslRuntime{

    struct BarryCentricCoordinates{
        float a;
        float b;
        float c;
    };

    class Runtime{
    public:
        explicit Runtime(const std::string& dataFile);

        ~Runtime();

        void execute();

    private:

        void vertexShaderStage();

        void primitiveAssemblyStage();

        void rasterizerStage();

        BarryCentricCoordinates calculateBarryCentricCoords(Vertex& v0, Vertex& v1, Vertex& v2, uint32_t x, uint32_t y);

        Vertex interpolateAttributes(Vertex& v0, Vertex& v1, Vertex& v2, BarryCentricCoordinates& bcc);



    private:
        Environment* m_Environment;
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;

        RenderTarget<uint8_t> m_ColorBuffer;
        RenderTarget<float> m_DepthBuffer;
    };

}