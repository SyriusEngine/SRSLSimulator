#include "ContextImpl.hpp"

namespace SrslAPI{

    ContextImpl::ContextImpl():
    m_Pipeline(new Pipeline()){

    }

    ContextImpl::~ContextImpl() {

    }

    void ContextImpl::draw() {

    }

    UP<VertexBuffer>
    ContextImpl::createVertexBuffer(const UP<VertexLayout> &layout, const void *data, uint32_t size) const {
        return createUP<VertexBufferImpl>(layout, data, size, m_Pipeline.get());
    }
}
