#pragma once

#include "Include.hpp"

namespace SrslAPI{

    struct SRSL_GRAPHICS_API Texture2DDesc{
        uint32_t width      = 0;
        uint32_t height     = 0;
        uint32_t channels   = 0;
        uint8_t *data       = nullptr;
        uint64_t dataSize   = 0;
    };

    struct SRSL_GRAPHICS_API ImageDesc{
        bool flipOnLoad = true;
        std::string path;
    };

    class SRSL_GRAPHICS_API Texture2D{
    public:
        explicit Texture2D(const Texture2DDesc& desc);

        explicit Texture2D(const ImageDesc& desc);

        virtual ~Texture2D();

        virtual void bind(uint32_t slot) = 0;

        [[nodiscard]] inline uint32_t getWidth() const{
            return m_Width;
        }

        [[nodiscard]] inline uint32_t getHeight() const{
            return m_Height;
        }

        [[nodiscard]] inline uint32_t getChannelCount() const{
            return m_ChannelCount;
        }

    protected:
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_ChannelCount;
    };
}