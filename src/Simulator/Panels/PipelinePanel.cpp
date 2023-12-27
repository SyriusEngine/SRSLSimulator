#include "PipelinePanel.hpp"

namespace Simulator{

    PipelinePanel::PipelinePanel(SimulatorStore& store):
    Panel(store, "Pipeline Overview", store.window->getWidth() / 5, store.window->getHeight() - store.navBar->panelHeight, 0, store.navBar->panelHeight){

    }

    void PipelinePanel::draw() {
        onBeginDraw();

        if (ImGui::CollapsingHeader("Vertex Layout")){

        }
        if (ImGui::CollapsingHeader("Mesh")){

        }
        if (ImGui::CollapsingHeader("Shader")){

        }
        if (ImGui::CollapsingHeader("Textures")){

        }
        if (ImGui::CollapsingHeader("Constant Buffers")){

        }

        onEndDraw();
    }
}
