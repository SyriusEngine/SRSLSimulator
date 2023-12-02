#include "ContextImpl.hpp"

namespace SrslAPI{

    ContextImpl::ContextImpl():
    m_Pipeline(new Pipeline()){

    }

    ContextImpl::~ContextImpl() {

    }

    void ContextImpl::draw() {
        m_Pipeline->execute();
    }

    UP<VertexBuffer>
    ContextImpl::createVertexBuffer(const UP<VertexLayout> &layout, const void *data, uint32_t size) const {
        return createUP<VertexBufferImpl>(layout, data, size, m_Pipeline.get());
    }
    UP<IndexBuffer> ContextImpl::createIndexBuffer(const uint32_t *data, uint32_t count) const {
        return createUP<IndexBufferImpl>(data, count, m_Pipeline.get());
    }

    UP<Shader> ContextImpl::createShader(const std::string &vertexShader, const std::string &fragmentShader) const {
        return createUP<ShaderImpl>(vertexShader, fragmentShader, m_Pipeline);
    }

    UP<FrameBuffer> ContextImpl::createFrameBuffer(const FrameBufferLayout &layout) const {
        return createUP<FrameBufferImpl>(layout, m_Pipeline.get());
    }

    UP<ConstantBuffer> ContextImpl::createConstantBuffer(const ConstantBufferDesc &desc) const {
        return createUP<ConstantBufferImpl>(desc, m_Pipeline);
    }
}
