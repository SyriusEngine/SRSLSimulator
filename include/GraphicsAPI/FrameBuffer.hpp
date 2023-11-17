#pragma once

#include "Include.hpp"
#include "ColorAttachment.hpp"

namespace SrslAPI{

    class SRSL_GRAPHICS_API FrameBufferLayout{
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

    class SRSL_GRAPHICS_API FrameBuffer{
    public:
        explicit FrameBuffer(const FrameBufferLayout& layout);

        virtual ~FrameBuffer() = default;

        virtual void bind() = 0;

        [[nodiscard]] inline const UP<ColorAttachment>& getColorAttachment(uint32_t index) const{
            return m_ColorAttachments[index];
        }

        [[nodiscard]] inline const UP<ColorAttachment>& operator[](uint32_t index) const {
            return m_ColorAttachments[index];
        }

    protected:
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_X;
        uint32_t m_Y;

        std::vector<UP<ColorAttachment>> m_ColorAttachments;
    };


}