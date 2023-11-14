#include "IndexBufferImpl.hpp"
#include "Pipeline.hpp"

namespace SrslAPI{

    IndexBufferImpl::IndexBufferImpl(const uint32_t *data, uint32_t count, Pipeline *pipeline):
    IndexBuffer(data, count),
    m_Pipeline(pipeline){

    }

    IndexBufferImpl::~IndexBufferImpl() {

    }

    void IndexBufferImpl::bind() {
        m_Pipeline->setIndexBuffer(this);
    }
}
