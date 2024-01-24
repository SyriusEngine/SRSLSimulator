#include "Display.hpp"

namespace Simulator{

    Display::Display(const std::string& configFile):
    m_Config(configFile),
    m_Renderer(m_Config){
        Syrius::WindowDesc wDesc;
        wDesc.title = "Simulator (Backend = OpenGL)";
        wDesc.width = m_Config["Display"]["Width"].getOrDefault<uint32>(DEF_WINDOW_WIDTH);
        wDesc.height = m_Config["Display"]["Height"].getOrDefault<uint32>(DEF_WINDOW_HEIGHT);
        wDesc.xPos = m_Config["Display"]["XPos"].getOrDefault<int32>(200);
        wDesc.yPos = m_Config["Display"]["YPos"].getOrDefault<int32>(200);

        m_Window = Syrius::createWindow(wDesc);

        Syrius::ContextDesc cDesc;
        cDesc.api = SR_API_OPENGL;
        m_Context = m_Window->createContext(cDesc);
        m_Context->setVerticalSynchronisation(true);

        auto fbWidth = m_Config["Renderer"]["FrameBufferWidth"].getOrDefault<uint32>(DEF_FRAMEBUFFER_WIDTH);
        auto fbHeight = m_Config["Renderer"]["FrameBufferHeight"].getOrDefault<uint32>(DEF_FRAMEBUFFER_HEIGHT);

        Syrius::Texture2DDesc tDesc;
        tDesc.width = fbWidth;
        tDesc.height = fbHeight;
        tDesc.format = SR_TEXTURE_RGBA_UI8;
        tDesc.data = nullptr;
        m_RenderTarget = m_Context->createTexture2D(tDesc);


        m_Window->createImGuiContext();

    }

    Display::~Display() {
        m_Window->destroyImGuiContext();
        m_Window->destroyContext();
    }

    void Display::run(){
        while (m_Window->isOpen()){
            m_Window->pollEvents();
            while (m_Window->hasEvent()){
                auto event = m_Window->getEvent();
                if (event.type == SR_EVENT_WINDOW_CLOSED){
                    m_Window->close();
                }
            }

            m_Context->beginRenderPass();

            m_Window->onImGuiBegin();

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(m_Renderer.getFrameBufferWidth() + 15, m_Window->getHeight()));
            ImGui::Begin("Simulator", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

            if (ImGui::Button("Clear")){
                m_Renderer.clear();
            }
            ImGui::SameLine();
            if (ImGui::Button("Render")){
                m_Renderer.render();
            }

            auto img = m_Renderer.getFrameBufferImage();
            m_RenderTarget->setData(img.data(), 0, 0, m_Renderer.getFrameBufferWidth(), m_Renderer.getFrameBufferHeight());
            ImGui::Image((void*)m_RenderTarget->getIdentifier(), ImVec2(m_Renderer.getFrameBufferWidth(), m_Renderer.getFrameBufferHeight()), ImVec2(0, 1), ImVec2(1, 0));

            ImGui::End();
            m_Window->onImGuiEnd();

            m_Context->endRenderPass();
            m_Context->swapBuffers();
        }
    }
}
