#include "RenderTargetPanel.hpp"

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