#include "Pipeline.hpp"
#include "../../include/GraphicsAPI/Profiler.hpp"

namespace SrslAPI{

    Pipeline::Pipeline():
    m_VertexBuffer(nullptr),
    m_IndexBuffer(nullptr),
    m_Shader(nullptr),
    m_FrameBuffer(nullptr){

    }

    Pipeline::~Pipeline() {

    }

    void Pipeline::execute() {
        checkState();
        RenderData data;


        SIM_START_TIME("RENDER::Vertex_shader")
        executeVertexShader(data);
        SIM_STOP_TIME("RENDER::Vertex_shader")
        SIM_START_TIME("RENDER::Rasterizer")
        rasterize(data);
        SIM_STOP_TIME("RENDER::Rasterizer")
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
        if(m_FrameBuffer == nullptr){
            throw std::runtime_error("Frame buffer is not set");
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

    void Pipeline::setFrameBuffer(FrameBufferImpl *frameBuffer) {
        m_FrameBuffer = frameBuffer;
    }

    void Pipeline::bindConstantBuffer(uint32_t slot, char *data) {
        m_ConstantBuffers[slot] = data;
    }

    void Pipeline::executeVertexShader(RenderData &data) {
        data.vertices.reserve(m_VertexBuffer->getCount());
        auto& vertices = m_VertexBuffer->getVertices();

        const auto width = static_cast<float>(m_FrameBuffer->m_Width);
        const auto height = static_cast<float>(m_FrameBuffer->m_Height);

        for (auto& vertex: vertices){
            data.vertices.push_back(m_Shader->executeVertexShader(vertex, m_ConstantBuffers));

            auto& processedVertex = data.vertices.back();

            // fill in the SRV_FRAGCOORD variable
            processedVertex["SRV_FRAGCOORD"] = glm::vec4(
                (processedVertex["SRV_POSITION"].x + 1.0f) * width / 2.0f,
                (processedVertex["SRV_POSITION"].y + 1.0f) * height / 2.0f,
                processedVertex["SRV_POSITION"].z,
                1.0f
            );
        }

    }

    void Pipeline::rasterize(RenderData &data) {
        if (m_IndexBuffer->getCount() % 3 != 0){
            throw std::runtime_error("Index buffer size is not a multiple of 3");
        }
        const auto& indices = m_IndexBuffer->getData();
        for (uint64_t i = 0; i < indices.size(); i += 3){
            auto& v0 = data.vertices[indices[i]];
            auto& v1 = data.vertices[indices[i + 1]];
            auto& v2 = data.vertices[indices[i + 2]];

            auto& v0FragCoord = v0["SRV_FRAGCOORD"];
            auto& v1FragCoord = v1["SRV_FRAGCOORD"];
            auto& v2FragCoord = v2["SRV_FRAGCOORD"];

            // bounding box
            uint32_t minX = std::min(v0FragCoord.x, std::min(v1FragCoord.x, v2FragCoord.x));
            uint32_t minY = std::min(v0FragCoord.y, std::min(v1FragCoord.y, v2FragCoord.y));
            uint32_t maxX = std::max(v0FragCoord.x, std::max(v1FragCoord.x, v2FragCoord.x));
            uint32_t maxY = std::max(v0FragCoord.y, std::max(v1FragCoord.y, v2FragCoord.y));

            // loop over the bounding box and check if the pixel is inside the triangle
            for (uint32_t x = minX; x <= maxX; x++) {
                for (uint32_t y = minY; y <= maxY; y++) {
                    float detT = (v1FragCoord.y - v2FragCoord.y) * (v0FragCoord.x - v2FragCoord.x) +
                                 (v2FragCoord.x - v1FragCoord.x) * (v0FragCoord.y - v2FragCoord.y);
                    float alpha = ((v1FragCoord.y - v2FragCoord.y) * (x - v2FragCoord.x) +
                                   (v2FragCoord.x - v1FragCoord.x) * (y - v2FragCoord.y)) / detT;
                    float beta = ((v2FragCoord.y - v0FragCoord.y) * (x - v2FragCoord.x) +
                                    (v0FragCoord.x - v2FragCoord.x) * (y - v2FragCoord.y)) / detT;
                    float gamma = 1.0f - alpha - beta;

                    if (alpha >= 0.0f && beta >= 0.0f && gamma >= 0.0f) {
                        InputFragment fragment = interpolate(v0, v1, v2, alpha, beta, gamma);

                        OutputFragment outputFragment = m_Shader->executeFragmentShader(fragment, m_ConstantBuffers);
                        glm::vec4 color = outputFragment["SRV_TARGET_0"];
                        m_FrameBuffer->m_ColorAttachments[0]->setPixel(x, y, color.r, color.g, color.b, color.a);
                    }
                }
            }
        }
    }

    InputFragment
    Pipeline::interpolate(const OutputVertex &v0, const OutputVertex &v1, const OutputVertex &v2, float alpha,
                          float beta, float gamma) {
        InputFragment fragment;
        for (const auto& [key, value]: v0){
            fragment[key] = alpha * value + beta * v1.at(key) + gamma * v2.at(key);
        }
        return fragment;
    }

}
