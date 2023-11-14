#pragma once

#include "Include.hpp"
#include "VertexLayout.hpp"
#include "VertexBuffer.hpp"

namespace SrslAPI{

    class SRSL_GRAPHICS_API Context{
    public:
        Context() = default;

        virtual ~Context() = default;

        [[nodiscard]] UP<VertexLayout> createVertexLayout() const;

        [[nodiscard]] virtual UP<VertexBuffer> createVertexBuffer(const UP<VertexLayout>& layout, const void* data, uint32_t size) const = 0;

        virtual void draw() = 0;
    };

}