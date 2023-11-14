#include "Pipeline.hpp"

namespace SrslAPI{

    Pipeline::Pipeline():
    m_VertexBuffer(nullptr),
    m_IndexBuffer(nullptr){

    }

    Pipeline::~Pipeline() {

    }

    void Pipeline::execute() {
        checkState();

    }

    void Pipeline::checkState() {
        if(m_VertexBuffer == nullptr){
            throw std::runtime_error("Vertex buffer is not set");
        }
        if(m_IndexBuffer == nullptr){
            throw std::runtime_error("Index buffer is not set");
        }

    }

    void Pipeline::setVertexBuffer(VertexBufferImpl *vertexBuffer) {
        m_VertexBuffer = vertexBuffer;
    }

    void Pipeline::setIndexBuffer(IndexBufferImpl *indexBuffer) {
        m_IndexBuffer = indexBuffer;
    }

}
