#pragma once

#include "GraphicsAPI/Texture2D.hpp"
#include "../Primitives.hpp"

namespace SrslAPI{

    class Pipeline;

    struct Texture2DData{
        uint32_t width;
        uint32_t height;
        uint32_t channels;
        std::vector<uint8_t> data;
    };

    class Texture2DImpl: public Texture2D{
    public:
        Texture2DImpl(const Texture2DDesc &desc, Pipeline *pipeline);

        Texture2DImpl(const ImageDesc &desc, Pipeline *pipeline);

        ~Texture2DImpl() override;

        void bind(uint32_t slot) override;

    private:
        Pipeline *m_Pipeline;

        Texture2DData m_Data;
    };


}