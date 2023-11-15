#pragma once

#include "../../include/GraphicsAPI/VertexBuffer.hpp"
#include "Primitives.hpp"

namespace SrslAPI{

    class Pipeline;

    class VertexBufferImpl: public VertexBuffer{
    public:
        VertexBufferImpl(const UP<VertexLayout>& layout, const void* data, uint32_t size, Pipeline* pipeline);

        ~VertexBufferImpl() override;

        void bind() override;

        [[nodiscard]] inline uint32_t getCount() const { return m_Count; }

        [[nodiscard]] inline std::vector<InputVertex>& getVertices() { return m_Vertices; }



    private:

        void createVertexData(const void* data);

    private:
        Pipeline* m_Pipeline;

        std::vector<InputVertex> m_Vertices;
        uint32_t m_Count;
    };
}