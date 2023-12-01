#pragma once

#include "SimulatorInclude.hpp"
#include "GraphicsAPI/Profiler.hpp"

namespace Simulator{

    class Simulator{
    public:
        Simulator();

        ~Simulator() = default;

        void run();

        void setupSrslAPI();

        void setupOpenGL();

    private:

        void renderSrsl();

        void renderImGui();

    private:
        Syrius::Resource<Syrius::SyriusWindow> m_Window;
        Syrius::ResourceView<Syrius::Context> m_OpenGLContext;

        UP<Context> m_SrslContext;
        UP<VertexBuffer> m_VertexBuffer;
        UP<VertexLayout> m_VertexLayout;
        UP<IndexBuffer> m_IndexBuffer;
        UP<Shader> m_Shader;
        UP<FrameBuffer> m_FrameBuffer;
        UP<ConstantBuffer> m_ConstantBuffer;

        Syrius::ResourceView<Syrius::Texture2D> m_Texture;

    };
}