#pragma once

#include "GraphicsAPI/Include.hpp"
#include "../Primitives.hpp"
#include "VertexBufferImpl.hpp"
#include "IndexBufferImpl.hpp"
#include "ShaderImpl.hpp"
#include "FrameBufferImpl.hpp"
#include "ConstantBufferImpl.hpp"
#include "Texture2DImpl.hpp"

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

        void bindConstantBuffer(uint32_t slot, char* data);

        void bindTexture(uint32_t slot, char* data);

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

        ConstantBuffers m_ConstantBuffers;
        Textures m_Textures;
        Samplers m_Samplers;
    };

}