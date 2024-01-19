#include "RenderTargetPanel.hpp"
#include "ShaderPanel.hpp"
#include <processthreadsapi.h>

namespace Simulator{

    RenderTargetPanel::RenderTargetPanel(SimulatorStore &store):
    Panel(store, "RenderTarget", 2 * store.window->getWidth() / 5, store.window->getHeight() - store.navBar->panelHeight, store.pipelinePanel->panelWidth, store.navBar->panelHeight),
    m_Debugger(nullptr){

        Syrius::Texture2DDesc desc;
        desc.width = DRAW_WIDTH;
        desc.height = DRAW_HEIGHT;
        desc.format = SR_TEXTURE_RGBA_UI8;
        desc.data = nullptr;
        m_RenderTargetView = m_Store.srContext->createTexture2D(desc);

    }

    void RenderTargetPanel::draw() {
        static bool showSaveDialog = false;
        panelX = m_Store.pipelinePanel->panelWidth;
        onBeginDraw();
        if (ImGui::Button("Render")){
            m_Store.renderer->draw();
        }
        ImGui::SameLine();
        if (ImGui::Button("Clear")){
            m_Store.renderer->frameBuffer->getColorAttachment(0)->clear();
        }
        ImGui::SameLine();
        if (m_Debugger == nullptr){
            if (ImGui::Button("Debug")){
                m_Debugger = createUP<Debugger>();

                auto vsPanel = dynamic_cast<ShaderPanel*>(m_Store.vertexShaderPanel.get());
                auto fsPanel = dynamic_cast<ShaderPanel*>(m_Store.fragmentShaderPanel.get());

                auto vsBreaks = vsPanel->getSelectedLines();
                auto fsBreaks = fsPanel->getSelectedLines();

                std::string vsFileLoc = "CompiledShaders/comp-vs.cpp";
                std::string fsFileLoc = "CompiledShaders/comp-fs.cpp";

                // first convert our SRSL line number to C++ line number
                if (!vsBreaks.empty()){
                    uint32 cppLine = m_Store.vertexShaderLineInfo[vsBreaks[0]][0];

                    // use absolute path to instruct GDB to break at the line
                    std::filesystem::path fullPath = std::filesystem::absolute(vsFileLoc);
                    std::string cmdBreakVs = "break " + fullPath.string() + ":" + std::to_string(cppLine);

                    // instruct GDB to break at the line
                    m_Debugger->sendCommand(cmdBreakVs);
                }
            }
        }
        else{
            if (ImGui::Button("Stop Debugging")){
                m_Debugger.reset();
            }
        }

        const auto& data = m_Store.renderer->frameBuffer->getColorAttachment(0)->getData();
        m_RenderTargetView->setData(data.data(), 0, 0, DRAW_WIDTH, DRAW_HEIGHT);
        ImGui::Image((void*)m_RenderTargetView->getIdentifier(), ImVec2(DRAW_WIDTH, DRAW_HEIGHT), ImVec2(0, 1), ImVec2(1, 0));

        if (ImGui::Button("Save")){
            showSaveDialog = true;
        }

        static uint64 processID = GetCurrentProcessId();
        ImGui::Text("Process ID: %llu", processID);

        if (m_Store.renderer->shader != nullptr){
            const auto& debugInfo = m_Store.renderer->shader->getDebugInfo();
            ImGui::Text("Vertex Shader Source:");
            ImGui::Text(debugInfo.vertexShaderSource.c_str());
            ImGui::Text("Vertex Shader Cpp Source:");
            ImGui::Text(debugInfo.vertexShaderCppSource.c_str());
            ImGui::Text("Vertex Shader Line Info:");
            ImGui::Text(debugInfo.vertexShaderLineInfo.c_str());

            ImGui::Text("Fragment Shader Source:");
            ImGui::Text(debugInfo.fragmentShaderSource.c_str());
            ImGui::Text("Fragment Shader Cpp Source:");
            ImGui::Text(debugInfo.fragmentShaderCppSource.c_str());
            ImGui::Text("Fragment Shader Line Info:");
            ImGui::Text(debugInfo.fragmentShaderLineInfo.c_str());

        }

        onEndDraw();

        if (showSaveDialog){
            ImGui::Begin("Save Dialog");
            static char fileName[64] = "";
            ImGui::InputText("File Name", fileName, 64);
            if (ImGui::Button("Save")){
                std::string filePath = m_Store.window->saveFileDialog(fileName, "");
                if (!filePath.empty()){
                    m_Store.renderer->frameBuffer->getColorAttachment(0)->save(filePath + ".png");
                }
                showSaveDialog = false;
            }
            if (ImGui::Button("Cancel")){
                showSaveDialog = false;
            }
            ImGui::End();
        }
    }

}