#pragma once

#include "GraphicsAPI/ConstantBuffer.hpp"
#include "../Primitives.hpp"

namespace SrslAPI{

    class Pipeline;

    class ConstantBufferImpl: public ConstantBuffer{
    public:
        ConstantBufferImpl(const ConstantBufferDesc& desc, const UP<Pipeline>& pipeline);

        ~ConstantBufferImpl() override = default;

        void setData(void* data, uint32_t size) override;

        void bind() const override;

    private:
        const UP<Pipeline>& m_Pipeline;
        UP<char[]> m_Data;

    };

}