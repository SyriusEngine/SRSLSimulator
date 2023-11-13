#pragma once

#include <vector>
#include <memory>
#include "stb_image_write.hpp"

namespace SrslRuntime{

    template<typename T>
    class RenderTarget{
    public:
        RenderTarget(uint32_t width, uint32_t height, uint32_t channelCount):
        m_Width(width),
        m_Height(height),
        m_ChannelCount(channelCount),
        m_Data(new T[width * height * channelCount]){
        }

        ~RenderTarget() = default;

        void save(const std::string& filename){
            if constexpr (std::is_same_v<T, float>){
                stbi_write_hdr(filename.c_str(), m_Width, m_Height, m_ChannelCount, reinterpret_cast<float*>(m_Data));
            }
            else if constexpr (std::is_same_v<T, uint8_t>){
                stbi_write_png(filename.c_str(), m_Width, m_Height, m_ChannelCount, reinterpret_cast<uint8_t*>(m_Data.get()), m_Width * m_ChannelCount);
            }
        }

        T& operator()(uint32_t x, uint32_t y, uint32_t channel){
            return m_Data[x + y * m_Width + channel * m_Width * m_Height];
        }

        const T& operator()(uint32_t x, uint32_t y, uint32_t channel) const{
            return m_Data[x + y * m_Width + channel * m_Width * m_Height];
        }

        void clear(const T& value){
            for(uint32_t i = 0; i < m_Width * m_Height * m_ChannelCount; ++i){
                m_Data[i] = value;
            }
        }

        [[nodiscard]] inline uint32_t getWidth() const{
            return m_Width;
        }

        [[nodiscard]] inline uint32_t getHeight() const{
            return m_Height;
        }

        [[nodiscard]] inline uint32_t getChannelCount() const{
            return m_ChannelCount;
        }


    private:
        uint32_t m_Width;
        uint32_t m_Height;
        uint32_t m_ChannelCount;
        std::unique_ptr<T[]> m_Data;
    };
}