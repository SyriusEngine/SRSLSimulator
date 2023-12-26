#include <iostream>
#include "Simulator.hpp"

namespace Simulator{

    Simulator::Simulator() {
        Syrius::WindowDesc windowDesc;
        windowDesc.title = "Simulator";
        windowDesc.width = SIM_WIDTH;
        windowDesc.height = SIM_HEIGHT;

        m_Window = Syrius::createWindow(windowDesc);

        Syrius::ContextDesc contextDesc;
        contextDesc.api = SR_API_OPENGL;
        m_OpenGLContext = m_Window->createContext(contextDesc);
        m_OpenGLContext->setVerticalSynchronisation(true);
        m_Window->createImGuiContext();

        setupSrslAPI();
        setupOpenGL();
    }

    void Simulator::run() {
        while(m_Window->isOpen()){
            m_Window->pollEvents();
            while(m_Window->hasEvent()){
                auto event = m_Window->getEvent();
                if(event.type == SR_EVENT_WINDOW_CLOSED){
                    m_Window->close();
                }
            }
            m_OpenGLContext->clear();

            renderImGui();

            m_OpenGLContext->swapBuffers();
        }

    }

    void Simulator::setupSrslAPI() {
        SIM_START_TIME("SrslAPI::Setup");
        m_SrslContext = createContext();

        m_VertexLayout = m_SrslContext->createVertexLayout();
        m_VertexLayout->pushAttribute("Position", SRSL_FLOAT32_3);
        m_VertexLayout->pushAttribute("Color", SRSL_FLOAT32_3);
        m_VertexLayout->pushAttribute("Normal", SRSL_FLOAT32_3);
        m_VertexLayout->pushAttribute("TexCoords", SRSL_FLOAT32_4);

        std::vector<Vertex> rectangle = {
                {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.f, 0.f, 0.f, 0.f, 0.f, 0.0f, 0.0f},
                {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, -1.f, 0.f, 0.f, 1.f, 0.f, 0.0f, 0.0f},
                {0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, -1.f, 0.f, 0.f, 1.f, 1.f, 0.0f, 0.0f},
                {-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, -1.f, 0.f, 0.f, 0.f, 1.f, 0.0f, 0.0f}
        };
        m_VertexBuffer = m_SrslContext->createVertexBuffer(m_VertexLayout, rectangle.data(), rectangle.size() * sizeof(Vertex));

        std::vector<uint32_t> indices = {
                0, 1, 2,
                2, 3, 0
        };
        m_IndexBuffer = m_SrslContext->createIndexBuffer(indices.data(), indices.size());

        SIM_START_TIME("SrslAPI::ShaderCompilation")
        m_Shader = m_SrslContext->createShader("./SRSLShaders/Basic-vs.srsl", "./SRSLShaders/Basic-fs.srsl");
        auto end_time = std::chrono::high_resolution_clock::now();
        SIM_STOP_TIME("SrslAPI::ShaderCompilation")

        ColorAttachmentDesc desc;
        desc.width = SIM_WIDTH;
        desc.height = SIM_HEIGHT;
        desc.channelCount = 4;
        desc.clearColor[0] = 0.2f;
        desc.clearColor[1] = 0.3f;
        desc.clearColor[2] = 0.8f;
        desc.clearColor[3] = 1.0f;

        FrameBufferLayout fbLayout;
        fbLayout.setViewport(1280, 720, 0, 0);
        fbLayout.addColorAttachment(desc);

        m_FrameBuffer = m_SrslContext->createFrameBuffer(fbLayout);
        m_FrameBuffer->getColorAttachment(0)->clear();

        glm::mat4 modelData(1.0f);
        ConstantBufferDesc cbd;
        cbd.name = "ModelData";
        cbd.size = sizeof(glm::mat4);
        cbd.data = &modelData;
        m_ConstantBuffer = m_SrslContext->createConstantBuffer(cbd);

        ImageDesc imgDesc;
        imgDesc.flipOnLoad = true;
        imgDesc.path = "./Resources/Textures/awesomeface.png";
        m_Texture = m_SrslContext->createTexture2D(imgDesc);
        SIM_STOP_TIME("SrslAPI::Setup");
    }

    void Simulator::setupOpenGL() {
        SIM_START_TIME("Syrius::OpenGLSetup");
        Syrius::Texture2DDesc desc;
        desc.width = SIM_WIDTH;
        desc.height = SIM_HEIGHT;
        desc.format = SR_TEXTURE_RGBA_UI8;
        desc.data = m_FrameBuffer->getColorAttachment(0)->getData().data();
        m_RenderTexture = m_OpenGLContext->createTexture2D(desc);
        SIM_STOP_TIME("Syrius::OpenGLSetup");

    }

    void Simulator::renderSrsl() {
        SIM_START_TIME("SrslAPI::Render");
        m_FrameBuffer->bind();
        m_VertexBuffer->bind();
        m_IndexBuffer->bind();
        m_ConstantBuffer->bind();
        m_Shader->bind();
        m_Texture->bind(0);

        m_SrslContext->draw();

        SIM_STOP_TIME("SrslAPI::Render");
    }

    void Simulator::renderImGui() {
        m_Window->onImGuiBegin();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(SIM_WIDTH / 5, SIM_HEIGHT));
        ImGui::Begin("Utils", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

        if (ImGui::Button("Render SRSL")) {
            renderSrsl();
            m_RenderTexture->setData(m_FrameBuffer->getColorAttachment(0)->getData().data(), 0, 0, SIM_WIDTH, SIM_HEIGHT);
        }
        // render timers in a table
        ImGui::Columns(2, "Timers");
        ImGui::Separator();
        ImGui::Text("Name"); ImGui::NextColumn();
        ImGui::Text("Time"); ImGui::NextColumn();
        ImGui::Separator();
        for (auto& timer : Timers::getDurations()) {
            ImGui::Text("%s", timer.first.c_str()); ImGui::NextColumn();
            ImGui::Text("%llu ms", timer.second); ImGui::NextColumn();
        }

        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(SIM_WIDTH / 5, 0));
        ImGui::SetNextWindowSize(ImVec2( 4 * SIM_WIDTH / 5 , SIM_HEIGHT));
        ImGui::Begin("Render", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::Image((void*)m_RenderTexture->getIdentifier(), ImVec2(2 * SIM_WIDTH / 3, 2 * SIM_HEIGHT / 3), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();

        m_Window->onImGuiEnd();
    }

}
