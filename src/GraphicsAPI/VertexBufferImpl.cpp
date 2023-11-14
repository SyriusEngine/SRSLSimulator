#include "VertexBufferImpl.hpp"
#include "Pipeline.hpp"

namespace SrslAPI{


    VertexBufferImpl::VertexBufferImpl(const UP<VertexLayout> &layout, const void *data, uint32_t size, Pipeline *pipeline):
    VertexBuffer(layout, data, size), m_Pipeline(pipeline) {
        if (size % layout->getStride() != 0) {
            throw std::runtime_error("[VertexBuffer][VertexBuffer]: size of data is not a multiple of the stride of the layout");
        }
        createVertexData(data);
    }

    VertexBufferImpl::~VertexBufferImpl() {
        for (auto& vertex: m_Vertices){
            for (auto& attr: vertex){
                delete[] attr.second;
            }
        }
    }

    void VertexBufferImpl::bind() {
        m_Pipeline->setVertexBuffer(this);
    }

    void VertexBufferImpl::createVertexData(const void *data) {
        // we know the layout and the amount of vertices
        // we can now create the vertices which are unordered maps
        const uint32_t stride = m_Layout->getStride();
        const auto& attributes = m_Layout->getAttributes();

        for (uint64_t i = 0; i < m_Size; i += stride){
            InputVertex vertex;

            // create individual buffers for each attribute
            uint32_t offset = 0;
            for (const auto& attr: attributes){
                vertex[attr.name] = new char[attr.size];
                memcpy(vertex[attr.name], (char*)data + i + offset, attr.size);
                offset += attr.size;
            }
            m_Vertices.push_back(vertex);
        }
    }
}
