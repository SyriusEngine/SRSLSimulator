#pragma once

#include "../../include/GraphicsAPI/ConstantBuffer.hpp"
#include "Primitives.hpp"
#include "VideoMemory.hpp"

namespace SrslAPI{

    class Pipeline;

    class ConstantBufferImpl: public ConstantBuffer{
    public:
        ConstantBufferImpl(const ConstantBufferDesc& desc, const UP<Pipeline>& pipeline, const UP<VideoMemory>& videoMemory);

        ~ConstantBufferImpl() override = default;

        void setData(void* data, uint32_t size) override;

        void bind() const override;

    private:
        const UP<Pipeline>& m_Pipeline;
        const UP<VideoMemory>& m_VideoMemory;

    };

}