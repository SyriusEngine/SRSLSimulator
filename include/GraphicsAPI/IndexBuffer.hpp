#pragma once

#include "Include.hpp"

namespace SrslAPI{

    class SRSL_GRAPHICS_API IndexBuffer{
    public:
        IndexBuffer(const uint32_t* data, uint32_t count):
        m_Data(std::vector<uint32_t>(data, data + count)),
        m_Count(count){

        }

        virtual ~IndexBuffer() = default;

        [[nodiscard]] inline uint32_t getCount() const { return m_Count; }

        virtual void bind() = 0;

        inline const std::vector<uint32_t>& getData() const { return m_Data; }

    protected:
        std::vector<uint32_t> m_Data;
        uint32_t m_Count;
    };
}