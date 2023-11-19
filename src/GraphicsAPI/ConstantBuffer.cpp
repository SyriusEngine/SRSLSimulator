#include "../../include/GraphicsAPI/ConstantBuffer.hpp"

namespace SrslAPI{

    ConstantBuffer::ConstantBuffer(const ConstantBufferDesc &desc):
    m_Size(desc.size),
    m_Slot(desc.slot),
    m_Name(desc.name){

    }

    const std::string &ConstantBuffer::getName() const {
        return m_Name;
    }

    uint32_t ConstantBuffer::getSize() const {
        return m_Size;
    }

    uint32_t ConstantBuffer::getSlot() const {
        return m_Slot;
    }
}
