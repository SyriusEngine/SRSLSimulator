#include "Pipeline.hpp"

namespace SrslAPI{

    Pipeline::Pipeline():
    m_VertexBuffer(nullptr){

    }

    Pipeline::~Pipeline() {

    }

    void Pipeline::execute() {

    }

    void Pipeline::setVertexBuffer(VertexBufferImpl *vertexBuffer) {
        m_VertexBuffer = vertexBuffer;
    }
}
