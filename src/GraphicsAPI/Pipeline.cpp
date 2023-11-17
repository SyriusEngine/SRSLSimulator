#include "Pipeline.hpp"

namespace SrslAPI{

    Pipeline::Pipeline():
    m_VertexBuffer(nullptr),
    m_IndexBuffer(nullptr),
    m_Shader(nullptr){

    }

    Pipeline::~Pipeline() {

    }

    void Pipeline::execute() {
        checkState();
        RenderData data;

        executeVertexShader(data);
        // TODO: remove this later
        for (auto& vertex: data.vertices){
            printf("Vertex: %f, %f, %f\n", vertex["SRV_POSITION"].x, vertex["SRV_POSITION"].y, vertex["SRV_POSITION"].z);
        }
        rasterize(data);
    }

    void Pipeline::checkState() {
        if(m_VertexBuffer == nullptr){
            throw std::runtime_error("Vertex buffer is not set");
        }
        if(m_IndexBuffer == nullptr){
            throw std::runtime_error("Index buffer is not set");
        }
        if(m_Shader == nullptr){
            throw std::runtime_error("Shader is not set");
        }

    }

    void Pipeline::setVertexBuffer(VertexBufferImpl *vertexBuffer) {
        m_VertexBuffer = vertexBuffer;
    }

    void Pipeline::setIndexBuffer(IndexBufferImpl *indexBuffer) {
        m_IndexBuffer = indexBuffer;
    }

    void Pipeline::setShader(ShaderImpl *shader) {
        m_Shader = shader;
    }

    void Pipeline::executeVertexShader(RenderData &data) {
        data.vertices.reserve(m_VertexBuffer->getCount());
        auto& vertices = m_VertexBuffer->getVertices();

        for (auto& vertex: vertices){
            data.vertices.push_back(m_Shader->executeVertexShader(vertex));

            auto& processedVertex = data.vertices.back();
        }

    }

    void Pipeline::rasterize(RenderData &data) {


    }

}
