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
            drawTextures();
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
        ImGui::Text("Vertices");
        const auto& attributes = m_Store.renderer->vertexLayout->getAttributes();
        if (attributes.size() > 0){
            ImGui::Columns(attributes.size(), "Vertices");
            ImGui::Separator();
            for (const auto& attribute : attributes){
                ImGui::Text(attribute.name.c_str()); ImGui::NextColumn();
            }
            ImGui::Separator();
            uint64 i = 0;
            for (auto& vertex : m_Store.vertices){
                for (auto& attribute : vertex){
                    const std::string ID = "##" + std::to_string(i++);
                    switch (attribute.size()) {
                        case 1: ImGui::InputFloat(ID.c_str(), &attribute[0]); break;
                        case 2: ImGui::InputFloat2(ID.c_str(), attribute.data()); break;
                        case 3: ImGui::InputFloat3(ID.c_str(), attribute.data()); break;
                        case 4: ImGui::InputFloat4(ID.c_str(), attribute.data()); break;
                        default: break;
                    }
                    ImGui::NextColumn();
                }
            }
            ImGui::Separator();
            ImGui::Columns(1);

            if (ImGui::Button("Add Vertex")){
                UIVertex vertex;
                for (const auto& attribute : attributes){
                    vertex.emplace_back(attribute.componentCount);
                }
                m_Store.vertices.emplace_back(vertex);
            }

            ImGui::Separator();
            ImGui::Text("Indices");
            for (auto& index : m_Store.indices){
                const std::string ID = "##Index" + std::to_string(i++);
                ImGui::InputInt(ID.c_str(), (int*)&index);
            }
            if (ImGui::Button("Add Index")){
                m_Store.indices.emplace_back();
            }

            ImGui::Separator();
            if (ImGui::Button("Load Mesh")){
                m_Store.renderer->loadMesh();
                printf("Loaded Mesh\n");
            }
        }
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

        ImGui::Separator();

        if (ImGui::Button("Load Shader")){
            m_Store.renderer->loadShaders(m_Store.vertexShaderPath, m_Store.fragmentShaderPath);
            printf("Loaded Shaders\n");
        }
    }

    void PipelinePanel::drawTextures() {
        if (!m_Store.textures.empty()){
            ImGui::Columns(2, "Textures");
            ImGui::Separator();
            ImGui::Text("Slot"); ImGui::NextColumn();
            ImGui::Text("Path"); ImGui::NextColumn();
            ImGui::Separator();
            for (const auto& tex : m_Store.textures){
                ImGui::Text("%d", tex.slot); ImGui::NextColumn();
                ImGui::Text(tex.path.c_str()); ImGui::NextColumn();
            }
            ImGui::Separator();
            ImGui::Columns(1);
        }

        ImGui::Text("Add Texture");
        static int slot = 0;
        ImGui::InputInt("Slot", &slot);
        static bool flipOnLoad = true;
        ImGui::Checkbox("Flip On Load", &flipOnLoad);
        if (ImGui::Button("Add Texture")){
            auto filePath = m_Store.window->openFileDialog("");
            if (!filePath.empty()){
                m_Store.renderer->loadTexture(filePath, slot, flipOnLoad);
            }
        }

    }

}
