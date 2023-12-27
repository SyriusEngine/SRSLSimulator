#include "NavBar.hpp"

namespace Simulator{

    NavBar::NavBar(SimulatorStore &store) :
    Panel(store, "NavBar", store.window->getWidth(), 20, 0, 0) {

    }

    void NavBar::draw() {
        static bool showSaveDialog = false;
        ImGui::SetNextWindowPos(ImVec2(panelX, panelY));
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight));
        ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoBackground |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_MenuBar |
                                       ImGuiWindowFlags_NoNavFocus);

        if(ImGui::BeginMenuBar()){
            if(ImGui::BeginMenu("File")){
                if(ImGui::MenuItem("Open")){
                    std::string filePath = m_Store.window->openFileDialog("");
                    if (!filePath.empty()){
                        m_Store.renderer->loadPipelineConfig(filePath);
                    }
                }
                if(ImGui::MenuItem("Save")){
                    showSaveDialog = true;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Render")) {
                if (ImGui::MenuItem("Render")) {

                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        onEndDraw();

        if (showSaveDialog){
            ImGui::Begin("Save Dialog");
            static char fileName[64] = "";
            ImGui::InputText("File Name", fileName, 64);
            if (ImGui::Button("Save")){
                std::string filePath = m_Store.window->saveFileDialog(fileName, "");
                if (!filePath.empty()){
                    m_Store.renderer->savePipelineConfig(filePath + ".json");
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
