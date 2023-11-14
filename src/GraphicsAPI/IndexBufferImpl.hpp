#pragma once

#include "../../include/GraphicsAPI/IndexBuffer.hpp"
#include "Primitives.hpp"

namespace SrslAPI {

    class Pipeline;

    class IndexBufferImpl : public IndexBuffer {
        public:
        IndexBufferImpl(const uint32_t* data, uint32_t count, Pipeline* pipeline);

        ~IndexBufferImpl() override;

        void bind() override;

    private:
        Pipeline* m_Pipeline;

    };
}