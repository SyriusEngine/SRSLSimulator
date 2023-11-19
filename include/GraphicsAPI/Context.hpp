#pragma once

#include "Include.hpp"
#include "VertexLayout.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "FrameBuffer.hpp"
#include "ConstantBuffer.hpp"

namespace SrslAPI{

    class SRSL_GRAPHICS_API Context{
    public:
        Context() = default;

        virtual ~Context() = default;

        [[nodiscard]] UP<VertexLayout> createVertexLayout() const;

        [[nodiscard]] virtual UP<VertexBuffer> createVertexBuffer(const UP<VertexLayout>& layout, const void* data, uint32_t size) const = 0;

        [[nodiscard]] virtual UP<IndexBuffer> createIndexBuffer(const uint32_t* data, uint32_t count) const = 0;

        [[nodiscard]] virtual UP<Shader> createShader(const std::string& vertexShader, const std::string& fragmentShader) const = 0;

        [[nodiscard]] virtual UP<FrameBuffer> createFrameBuffer(const FrameBufferLayout& layout) const = 0;

        [[nodiscard]] virtual UP<ConstantBuffer> createConstantBuffer(const ConstantBufferDesc& desc) const = 0;

        virtual void draw() = 0;
    };

}