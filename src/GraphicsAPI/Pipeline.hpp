#pragma once

#include "../../include/GraphicsAPI/Include.hpp"
#include "Primitives.hpp"
#include "VertexBufferImpl.hpp"

namespace SrslAPI{

    class Pipeline{
    public:
        Pipeline();

        ~Pipeline();

        void execute();

        void setVertexBuffer(VertexBufferImpl* vertexBuffer);

    private:
        VertexBufferImpl* m_VertexBuffer;

    };

}