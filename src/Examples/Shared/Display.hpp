#pragma once

#include "Include.hpp"
#include "Renderer.hpp"

namespace Simulator{

    class Display{
    public:
        explicit Display(const std::string& configFile);

        ~Display();

        void run();

        template<typename T, typename... Args>
        void addLayer(Args&&... args){
            m_Renderer.addLayer<T>(std::forward<Args>(args)...);
        }

    private:
        Renderer m_Renderer;
        EasyIni::Configuration m_Config;

        // display stuff
        Syrius::Resource<Syrius::SyriusWindow> m_Window;
        Syrius::ResourceView<Syrius::Context> m_Context;
        Syrius::ResourceView<Syrius::Texture2D> m_RenderTarget;


    };
}