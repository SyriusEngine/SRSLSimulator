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

        inline InputVertex& operator[](uint32_t index){
            return m_Vertices[index];
        }

        typename std::vector<InputVertex>::iterator begin(){
            return m_Vertices.begin();
        }

        typename std::vector<InputVertex>::iterator end(){
            return m_Vertices.end();
        }

        [[nodiscard]] inline uint32_t getCount() const { return m_Count; }

    private:

        void createVertexData(const void* data);

    private:
        Pipeline* m_Pipeline;

        std::vector<InputVertex> m_Vertices;
        uint32_t m_Count;
    };
}