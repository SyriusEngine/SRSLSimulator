#pragma once

#include "../../include/GraphicsAPI/FrameBuffer.hpp"
#include "Primitives.hpp"

namespace SrslAPI{

    class Pipeline;

    class FrameBufferImpl: public FrameBuffer{
    public:
        FrameBufferImpl(const FrameBufferLayout& layout, Pipeline* pipeline);

        ~FrameBufferImpl() override;

        void bind() override;

    private:

        friend class Pipeline;

    private:
        Pipeline* m_Pipeline;
    };

}