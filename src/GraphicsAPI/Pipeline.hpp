#pragma once

#include "../../include/GraphicsAPI/Include.hpp"
#include "Primitives.hpp"
#include "VertexBufferImpl.hpp"
#include "IndexBufferImpl.hpp"
#include "ShaderImpl.hpp"
#include "FrameBufferImpl.hpp"

namespace SrslAPI{

    struct RenderData{
        std::vector<OutputVertex> vertices;
        std::vector<OutputFragment> fragments;
    };

    class Pipeline{
    public:
        Pipeline();

        ~Pipeline();

        void execute();

        void setVertexBuffer(VertexBufferImpl* vertexBuffer);

        void setIndexBuffer(IndexBufferImpl* indexBuffer);

        void setShader(ShaderImpl* shader);

        void setFrameBuffer(FrameBufferImpl* frameBuffer);

        void checkState();

    private:

        void executeVertexShader(RenderData& data);

        void rasterize(RenderData& data);

        InputFragment interpolate(const OutputVertex& v0, const OutputVertex& v1, const OutputVertex& v2, float alpha, float beta, float gamma);


    private:
        VertexBufferImpl* m_VertexBuffer;
        IndexBufferImpl* m_IndexBuffer;
        ShaderImpl* m_Shader;
        FrameBufferImpl* m_FrameBuffer;

    };

}