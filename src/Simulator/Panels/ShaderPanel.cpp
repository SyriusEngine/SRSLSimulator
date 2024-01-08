#include "ShaderPanel.hpp"

namespace Simulator{

    ShaderPanel::ShaderPanel(SimulatorStore &store, const std::string &name, uint32 xPos):
    Panel(store, name, store.window->getWidth() / 5, store.window->getHeight() - store.navBar->panelHeight, xPos, store.navBar->panelHeight){

    }

    void ShaderPanel::draw() {
        onBeginDraw();

        if (!m_ShaderSource.empty()){
            const auto ID = "ShaderPanel" + name;
            ImGui::Columns(3, ID.c_str(), false);
            ImGui::SetColumnWidth(0, ImGui::GetFontSize() * 2);
            ImGui::SetColumnWidth(1, ImGui::GetFontSize() * 2);
            for (uint32 lineNr = 1; lineNr <= m_ShaderSource.size(); lineNr++){
                ImGui::Text("%d", lineNr);
                ImGui::NextColumn();

                bool selected = std::find(m_SelectedLines.begin(), m_SelectedLines.end(), lineNr) != m_SelectedLines.end();
                ImGui::Checkbox(("##Checkbox" + std::to_string(lineNr)).c_str(), &selected);
                if (ImGui::IsItemClicked()) {
                    // Toggle the state of the checkbox on click
                    auto it = std::find(m_SelectedLines.begin(), m_SelectedLines.end(), lineNr);
                    if (it != m_SelectedLines.end()) {
                        m_SelectedLines.erase(it);
                    } else {
                        m_SelectedLines.push_back(lineNr);
                    }
                }
                ImGui::NextColumn();

                ImGui::Text(m_ShaderSource[lineNr - 1].c_str());
                ImGui::NextColumn();
            }

            ImGui::Columns(1);

        }

        onEndDraw();
    }

    void ShaderPanel::loadShader(const std::string &shaderPath) {
        std::ifstream file(shaderPath);
        std::string line;
        while (std::getline(file, line)){
            m_ShaderSource.push_back(line);
        }
    }

    const std::vector<uint32> &ShaderPanel::getSelectedLines() const {
        return m_SelectedLines;
    }
}