#include "ConstantBufferImpl.hpp"
#include "Pipeline.hpp"

namespace SrslAPI{

    ConstantBufferImpl::ConstantBufferImpl(const ConstantBufferDesc &desc, const UP<Pipeline> &pipeline):
    ConstantBuffer(desc),
    m_Pipeline(pipeline),
    m_Data(createUP<char[]>(desc.size)){
        memcpy(m_Data.get(), desc.data, desc.size);
    }

    void ConstantBufferImpl::setData(void *data, uint32_t size) {
        if (size != m_Size){
            throw std::runtime_error("ConstantBufferImpl::setData: size mismatch");
        }
        memcpy(m_Data.get(), data, size);
    }

    void ConstantBufferImpl::bind() const {
        m_Pipeline->bindConstantBuffer(m_Slot, m_Data.get());
    }
}