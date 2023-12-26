#include "../../include/GraphicsAPI/ColorAttachment.hpp"
#include "Dependencies/stb_image_write.hpp"

namespace SrslAPI{

    ColorAttachment::ColorAttachment(const ColorAttachmentDesc &desc):
    m_Width(desc.width),
    m_Height(desc.height),
    m_ChannelCount(desc.channelCount),
    m_Data(desc.width * desc.height * desc.channelCount){
        for (uint32_t i = 0; i < 4; i++){
            m_ClearColor[i] = desc.clearColor[i];
        }
    }

    void ColorAttachment::clear() {
        for (uint32_t i = 0; i < m_Data.size(); i += m_ChannelCount){
            m_Data[i] = static_cast<uint8_t>(m_ClearColor[0] * 255);
            m_Data[i + 1] = static_cast<uint8_t>(m_ClearColor[1] * 255);
            m_Data[i + 2] = static_cast<uint8_t>(m_ClearColor[2] * 255);
            m_Data[i + 3] = static_cast<uint8_t>(m_ClearColor[3] * 255);
        }

    }

    void ColorAttachment::setPixel(uint32_t x, uint32_t y, float r, float g, float b, float a) {
        uint32_t index = (y * m_Width + x) * m_ChannelCount;
        // check if bounding box requested a pixel outside the image
        if (index >= m_Data.size()){
            return;
        }
        m_Data[index] = static_cast<uint8_t>(r * 255);
        m_Data[index + 1] = static_cast<uint8_t>(g * 255);
        m_Data[index + 2] = static_cast<uint8_t>(b * 255);
        m_Data[index + 3] = static_cast<uint8_t>(a * 255);
    }

    void ColorAttachment::save(const std::string &path) const {
        stbi_flip_vertically_on_write(true);
        stbi_write_png(path.c_str(), m_Width, m_Height, m_ChannelCount, m_Data.data(), m_Width * m_ChannelCount);
    }
}
