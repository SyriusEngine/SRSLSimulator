#include "PipelinePanel.hpp"

namespace Simulator{

    PipelinePanel::PipelinePanel(SimulatorStore& store):
    Panel(store, "Pipeline Overview", store.window->getWidth() / 5, store.window->getHeight() - store.navBar->panelHeight, 0, store.navBar->panelHeight){

    }

    void PipelinePanel::draw() {
        onBeginDraw();

        if (ImGui::CollapsingHeader("Vertex Layout")){
            drawVertexLayout();
        }
        if (ImGui::CollapsingHeader("Mesh")){
            drawMesh();
        }
        if (ImGui::CollapsingHeader("Shader")){
            drawShaders();
        }
        if (ImGui::CollapsingHeader("Textures")){

        }
        if (ImGui::CollapsingHeader("Constant Buffers")){

        }
        if (ImGui::CollapsingHeader("Background Color")){
            ImGui::ColorEdit4("Background Color", m_Store.renderer->frameBuffer->getColorAttachment(0)->getClearColor());
        }

        onEndDraw();
    }

    void PipelinePanel::drawVertexLayout() {
        ImGui::Columns(2, "VertexLayoutColumns");
        ImGui::Separator();
        ImGui::Text("Name"); ImGui::NextColumn();
        ImGui::Text("Components"); ImGui::NextColumn();
        ImGui::Separator();

        auto attr = m_Store.renderer->vertexLayout->getAttributes();
        for (const auto& attribute : attr){
            ImGui::Text(attribute.name.c_str()); ImGui::NextColumn();
            ImGui::Text("%d", attribute.componentCount); ImGui::NextColumn();
            ImGui::Separator();
        }
        ImGui::Columns(1);

        static bool showAddNewAttributeWindow = false;
        if (!showAddNewAttributeWindow){
            if (ImGui::Button("Add New Attribute")){
                showAddNewAttributeWindow = true;
            }
        }
        if (showAddNewAttributeWindow){
            static char newAttributeName[64] = "";
            static uint32 newAttributeComponentCount = 0;
            ImGui::BeginChild("Add New Attribute");
            ImGui::InputText("Name", newAttributeName, 64);
            ImGui::InputScalar("Component Count", ImGuiDataType_U32, &newAttributeComponentCount);
            if (ImGui::Button("Add")){
                m_Store.renderer->vertexLayout->pushAttribute(newAttributeName, cCountToType(newAttributeComponentCount));
                showAddNewAttributeWindow = false;
                newAttributeName[0] = '\0';
            }
            if (ImGui::Button("Cancel")){
                showAddNewAttributeWindow = false;
                newAttributeName[0] = '\0';
            }
            ImGui::EndChild();
        }
    }

    void PipelinePanel::drawMesh() {

    }

    void PipelinePanel::drawShaders() {
        if (ImGui::Button("Select Vertex Shader")){
            m_Store.vertexShaderPath = m_Store.window->openFileDialog("");
        }
        ImGui::SameLine();
        ImGui::Text(m_Store.vertexShaderPath.c_str());

        if (ImGui::Button("Select Fragment Shader")){
            m_Store.fragmentShaderPath = m_Store.window->openFileDialog("");
        }
        ImGui::SameLine();
        ImGui::Text(m_Store.fragmentShaderPath.c_str());

        if (ImGui::Button("Load")){
            m_Store.renderer->loadShaders(m_Store.vertexShaderPath, m_Store.fragmentShaderPath);
        }
    }

}
