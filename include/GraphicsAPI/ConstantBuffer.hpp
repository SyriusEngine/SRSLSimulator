#pragma once

#include "Include.hpp"

namespace SrslAPI{

    struct ConstantBufferDesc{
        std::string name;
        uint32_t size = 0;
        uint32_t slot = 0;
        void* data = nullptr;
    };

    class SRSL_GRAPHICS_API ConstantBuffer{
    public:
        explicit ConstantBuffer(const ConstantBufferDesc& desc);

        virtual ~ConstantBuffer() = default;

        virtual void setData(void* data, uint32_t size) = 0;

        virtual void bind() const = 0;

        [[nodiscard]] const std::string& getName() const;

        [[nodiscard]] uint32_t getSize() const;

        [[nodiscard]] uint32_t getSlot() const;

    protected:
        std::string m_Name;
        uint32_t m_Size;
        uint32_t m_Slot;

    };

}