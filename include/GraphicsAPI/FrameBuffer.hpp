#pragma once

#include "Include.hpp"
#include "ColorAttachment.hpp"

namespace SrslAPI{

    class FrameBufferLayout{
    public:
        FrameBufferLayout();

        ~FrameBufferLayout() = default;

        void setViewport(uint32_t width, uint32_t height, uint32_t x, uint32_t y);

        void addColorAttachment(const ColorAttachmentDesc& desc);

    private:
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_X;
        uint32_t m_Y;

        std::vector<ColorAttachmentDesc> m_ColorAttachmentDesc;

        friend class FrameBuffer;
    };

    class FrameBuffer{
    public:
        explicit FrameBuffer(const FrameBufferLayout& layout);

        ~FrameBuffer() = default;

        virtual void bind() = 0;

    protected:
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_X;
        uint32_t m_Y;

        std::vector<UP<ColorAttachment>> m_ColorAttachments;
    };


}