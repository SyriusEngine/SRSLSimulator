#pragma once

#include "../../include/GraphicsAPI/Context.hpp"
#include "VertexBufferImpl.hpp"
#include "IndexBufferImpl.hpp"
#include "ShaderImpl.hpp"
#include "FrameBufferImpl.hpp"
#include "ConstantBufferImpl.hpp"

#include "Pipeline.hpp"
#include "VideoMemory.hpp"

namespace SrslAPI{

    class ContextImpl: public Context{
    public:
        ContextImpl();

        ~ContextImpl() override;

        [[nodiscard]] UP<VertexBuffer> createVertexBuffer(const UP<VertexLayout>& layout, const void* data, uint32_t size) const override;

        [[nodiscard]] UP<IndexBuffer> createIndexBuffer(const uint32_t* data, uint32_t count) const override;

        [[nodiscard]] UP<Shader> createShader(const std::string& vertexShader, const std::string& fragmentShader) const override;

        [[nodiscard]] UP<FrameBuffer> createFrameBuffer(const FrameBufferLayout& layout) const override;

        [[nodiscard]] UP<ConstantBuffer> createConstantBuffer(const ConstantBufferDesc& desc) const override;

        void draw() override;

    private:
        UP<Pipeline> m_Pipeline;
        UP<VideoMemory> m_VideoMemory;

    };

}