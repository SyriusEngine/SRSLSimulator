#include <stdexcept>
#include "VideoMemory.hpp"

namespace SrslAPI{

    VideoMemory::~VideoMemory() {
        for (auto& buffer: m_ConstantBuffers){
            delete[] buffer.second;
        }
    }

    void VideoMemory::setConstantBuffer(const std::string &name, void *data, uint32_t size) {
        auto it = m_ConstantBuffers.find(name);
        if (it == m_ConstantBuffers.end()){
            m_ConstantBuffers[name] = new char[size];
            it = m_ConstantBuffers.find(name);
        }
        memcpy(it->second, data, size);
    }

    char *VideoMemory::getConstantBuffer(const std::string &name) {
        auto it = m_ConstantBuffers.find(name);
        if (it == m_ConstantBuffers.end()){
            throw std::runtime_error("Constant buffer not found");
        }
        return it->second;
    }
}
