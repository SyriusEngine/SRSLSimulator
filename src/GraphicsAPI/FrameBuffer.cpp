#include "../../include/GraphicsAPI/FrameBuffer.hpp"

namespace SrslAPI{

    FrameBufferLayout::FrameBufferLayout():
        m_Width(0),
        m_Height(0),
        m_X(0),
        m_Y(0)
    {

    }

    void FrameBufferLayout::setViewport(uint32_t width, uint32_t height, uint32_t x, uint32_t y) {
        m_Width = width;
        m_Height = height;
        m_X = x;
        m_Y = y;
    }

    void FrameBufferLayout::addColorAttachment(const ColorAttachmentDesc &desc) {
        m_ColorAttachmentDesc.push_back(desc);
    }

    FrameBuffer::FrameBuffer(const FrameBufferLayout &layout):
    m_Width(layout.m_Width),
    m_Height(layout.m_Height),
    m_X(layout.m_X),
    m_Y(layout.m_Y){
        for (auto& desc: layout.m_ColorAttachmentDesc){
            m_ColorAttachments.push_back(createUP<ColorAttachment>(desc));
        }

    }
}
