#pragma once

#include <string>
#include <unordered_map>

namespace SrslAPI{

    class VideoMemory{
    public:
        VideoMemory() = default;

        ~VideoMemory();

        void setConstantBuffer(const std::string& name, void* data, uint32_t size);

        char* getConstantBuffer(const std::string& name);

    private:
        std::unordered_map<std::string, char*> m_ConstantBuffers;
    };

}