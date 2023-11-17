#pragma once

#include "Include.hpp"

namespace SrslAPI{

    struct ColorAttachmentDesc{
        uint32_t width = 1280;
        uint32_t height = 720;
        uint8_t channelCount = 4;
    };

    class ColorAttachment{
    public:
        explicit ColorAttachment(const ColorAttachmentDesc& desc);

        ~ColorAttachment() = default;

        void clear(float r, float g, float b, float a);

        void setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a);

        void save(const std::string& path) const;

    protected:
        uint32_t m_Width;
        uint32_t m_Height;
        uint8_t m_ChannelCount;

        std::vector<uint8_t> m_Data;
    };

}
