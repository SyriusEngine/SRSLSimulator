#include "Panel.hpp"

namespace Simulator{

    Panel::Panel(SimulatorStore& store, const std::string& name, uint32 width, uint32 height, uint32 x, uint32 y):
    m_Store(store),
    panelWidth(width),
    panelHeight(height),
    panelX(x),
    panelY(y),
    name(name){

    }

    void Panel::onBeginDraw() {
        ImGui::SetNextWindowPos(ImVec2(panelX, panelY));
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight));
        ImGui::Begin(name.c_str(), nullptr, ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus);

    }

    void Panel::onEndDraw() {
        auto panelSize = ImGui::GetWindowSize();
        panelWidth = panelSize.x;
        panelHeight = panelSize.y;
        auto panelPos = ImGui::GetWindowPos();
        panelX = panelPos.x;
        panelY = panelPos.y;
        ImGui::End();

    }

}
