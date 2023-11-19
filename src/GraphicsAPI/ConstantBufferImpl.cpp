#include "ConstantBufferImpl.hpp"
#include "Pipeline.hpp"

namespace SrslAPI{

    ConstantBufferImpl::ConstantBufferImpl(const ConstantBufferDesc &desc, const UP<Pipeline> &pipeline, const UP<VideoMemory> &videoMemory):
    ConstantBuffer(desc),
    m_Pipeline(pipeline),
    m_VideoMemory(videoMemory){
        m_VideoMemory->setConstantBuffer(m_Name, desc.data, desc.size);
    }

    void ConstantBufferImpl::setData(void *data, uint32_t size) {
        m_VideoMemory->setConstantBuffer(m_Name, data, size);
    }

    void ConstantBufferImpl::bind() const {

    }
}