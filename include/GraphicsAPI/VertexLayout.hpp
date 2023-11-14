#pragma once

#include "Include.hpp"

namespace SrslAPI{

    struct SRSL_GRAPHICS_API VertexAttribute{
        std::string name;
        uint8_t typeSize = 0;
        uint8_t componentCount = 0;
        uint32_t size = 0;
    };

    class SRSL_GRAPHICS_API VertexLayout{
    public:
        VertexLayout();

        ~VertexLayout() = default;

        void pushAttribute(const std::string& name, SRSL_SCALAR_TYPE type);

        [[nodiscard]] inline const std::vector<VertexAttribute>& getAttributes() const { return m_Attributes; }

        [[nodiscard]] inline uint32_t getStride() const { return m_Stride; }

    private:
        std::vector<VertexAttribute> m_Attributes;
        uint32_t m_Stride;



    };

}