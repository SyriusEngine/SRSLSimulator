#pragma once

#include "Include.hpp"
#include "VertexLayout.hpp"

namespace SrslAPI{

    class SRSL_GRAPHICS_API VertexBuffer{
    public:
        VertexBuffer(const UP<VertexLayout>& layout, const void* data, uint32_t size):
        m_Layout(layout),
        m_Size(size){

        }

        virtual ~VertexBuffer() = default;

        [[nodiscard]] inline const UP<VertexLayout>& getLayout() const { return m_Layout; }

        virtual void bind() = 0;

    protected:
        const UP<VertexLayout>& m_Layout;
        uint32_t m_Size;

    };

}