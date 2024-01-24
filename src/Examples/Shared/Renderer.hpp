#pragma once

#include "Include.hpp"
#include "Layer.hpp"
#include "Worker.hpp"

namespace Simulator{

    class Renderer{
    public:
        explicit Renderer(EasyIni::Configuration& config);

        template<typename T, typename... Args>
        void addLayer(Args&&... args){
            m_Layers.emplace_back(createUP<T>(m_Context, std::forward<Args>(args)...));
        }

        void render();

        void clear();

        [[nodiscard]] uint32 getFrameBufferWidth() const;

        [[nodiscard]] uint32 getFrameBufferHeight() const;

        [[nodiscard]] const std::vector<uint8_t>& getFrameBufferImage() const;

    private:
        EasyIni::Configuration& m_Config;

        Worker m_RenderThread;

        UP<Context> m_Context;
        UP<FrameBuffer> m_FrameBuffer;

        std::vector<UP<Layer>> m_Layers;

    };

}