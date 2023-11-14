#pragma once

#include "../../include/GraphicsAPI/Include.hpp"
#include "Primitives.hpp"
#include "VertexBufferImpl.hpp"
#include "IndexBufferImpl.hpp"

namespace SrslAPI{

    class Pipeline{
    public:
        Pipeline();

        ~Pipeline();

        void execute();

        void setVertexBuffer(VertexBufferImpl* vertexBuffer);

        void setIndexBuffer(IndexBufferImpl* indexBuffer);

        void checkState();

    private:
        VertexBufferImpl* m_VertexBuffer;
        IndexBufferImpl* m_IndexBuffer;

    };

}