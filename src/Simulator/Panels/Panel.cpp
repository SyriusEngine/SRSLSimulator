#include "Panel.hpp"

namespace Simulator{

    Panel::Panel(SimulatorStore& store, uint32 width, uint32 height, uint32 x, uint32 y):
    m_Store(store),
    panelWidth(width),
    panelHeight(height),
    panelX(x),
    panelY(y){

    }

    void Panel::onBeginDraw() {
        ImGui::SetNextWindowPos(ImVec2(panelX, panelY));
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight));
        ImGui::Begin("Panel", nullptr, ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoTitleBar |
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
