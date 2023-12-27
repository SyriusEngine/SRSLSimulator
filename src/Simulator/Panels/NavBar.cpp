#include "NavBar.hpp"

namespace Simulator{

    NavBar::NavBar(SimulatorStore &store) :
    Panel(store, "NavBar", store.window->getWidth(), 20, 0, 0) {

    }

    void NavBar::draw() {
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

                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        onEndDraw();
    }
}
