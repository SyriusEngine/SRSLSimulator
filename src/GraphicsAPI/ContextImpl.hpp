#pragma once

#include "../../include/GraphicsAPI/Context.hpp"
#include "VertexBufferImpl.hpp"
#include "Pipeline.hpp"

namespace SrslAPI{

    class ContextImpl: public Context{
    public:
        ContextImpl();

        ~ContextImpl() override;

        [[nodiscard]] UP<VertexBuffer> createVertexBuffer(const UP<VertexLayout>& layout, const void* data, uint32_t size) const override;

        void draw() override;

    private:
        UP<Pipeline> m_Pipeline;

    };

}