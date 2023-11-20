#pragma once

#include "Include.hpp"

namespace SrslAPI{

    struct SRSL_GRAPHICS_API ColorAttachmentDesc{
        uint32_t width = 1280;
        uint32_t height = 720;
        uint8_t channelCount = 4;
        float clearColor[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    };

    class SRSL_GRAPHICS_API ColorAttachment{
    public:
        explicit ColorAttachment(const ColorAttachmentDesc& desc);

        ~ColorAttachment() = default;

        void clear();

        void setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a);

        void save(const std::string& path) const;

        [[nodiscard]] const std::vector<uint8_t>& getData() const { return m_Data; }

        [[nodiscard]] uint32_t getWidth() const { return m_Width; }

        [[nodiscard]] uint32_t getHeight() const { return m_Height; }

        [[nodiscard]] uint8_t getChannelCount() const { return m_ChannelCount; }

    protected:
        uint32_t m_Width;
        uint32_t m_Height;
        uint8_t m_ChannelCount;
        float m_ClearColor[4];

        std::vector<uint8_t> m_Data;
    };

}
