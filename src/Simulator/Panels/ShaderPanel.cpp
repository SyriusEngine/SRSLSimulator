#include "ShaderPanel.hpp"

namespace Simulator{

    ShaderPanel::ShaderPanel(SimulatorStore &store, const std::string &name, uint32 xPos):
    Panel(store, name, store.window->getWidth() / 5, store.window->getHeight() - store.navBar->panelHeight, xPos, store.navBar->panelHeight){

    }

    void ShaderPanel::draw() {
        onBeginDraw();

        if (!m_ShaderSource.empty()){
            const std::string& id = "Shader" + name;
            ImGui::InputTextMultiline(id.c_str(), &m_ShaderSource[0], m_ShaderSource.size(), ImVec2(panelWidth, panelHeight));

        }

        onEndDraw();
    }

    void ShaderPanel::loadShader(const std::string &shaderPath) {
        std::ifstream file(shaderPath);
        std::string line;
        while (std::getline(file, line)){
            m_ShaderSource += line + "\n";
        }
    }
}