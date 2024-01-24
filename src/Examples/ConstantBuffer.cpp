#include "ConstantBuffer.hpp"

namespace Simulator{

    ConstantBufferLayer::ConstantBufferLayer(UP<Context>& context):
    Layer(context),
    m_MixDataStruct(),
    m_ModelDataStruct(),
    m_Translation(0.0f, 0.0f, 0.0f),
    m_Scale(1.0f, 1.0f, 1.0f),
    m_Rotation(0.0f, 0.0f, 0.0f){
        m_VertexBuffer = m_Context->createVertexBuffer(
                m_VertexLayout,
                s_RectangleVertices,
                sizeof(s_RectangleVertices)
        );
        m_IndexBuffer = m_Context->createIndexBuffer(
                s_RectangleIndices,
                6
        );
        m_Shader = m_Context->createShader(
                "./ExampleShaders/ConstantBuffer-vs.srsl",
                "./ExampleShaders/ConstantBuffer-fs.srsl"
        );

        ImageDesc awesomeFaceDesc;
        awesomeFaceDesc.flipOnLoad = true;
        awesomeFaceDesc.path = "./Resources/Textures/awesomeface.png";
        m_AwesomeFace = m_Context->createTexture2D(awesomeFaceDesc);

        ImageDesc instagramLogoDesc;
        instagramLogoDesc.flipOnLoad = true;
        instagramLogoDesc.path = "./Resources/Textures/insta.png";
        m_InstagramLogo = m_Context->createTexture2D(instagramLogoDesc);

        ConstantBufferDesc modelDataDesc;
        modelDataDesc.size = sizeof(ModelData);
        modelDataDesc.data = &m_ModelDataStruct;
        modelDataDesc.slot = 0;
        modelDataDesc.name = "ModelData";
        m_ModelData = m_Context->createConstantBuffer(modelDataDesc);

        ConstantBufferDesc mixDesc;
        mixDesc.size = sizeof(MixData);
        mixDesc.data = &m_MixDataStruct;
        mixDesc.slot = 1;
        mixDesc.name = "MixData";
        m_MixData = m_Context->createConstantBuffer(mixDesc);
    }

    void ConstantBufferLayer::onRender() {
        m_VertexBuffer->bind();
        m_IndexBuffer->bind();

        m_Shader->bind();

        m_AwesomeFace->bind(0);
        m_InstagramLogo->bind(1);

        m_ModelData->bind();
        m_MixData->bind();
        m_Context->draw();
    }

    void ConstantBufferLayer::onImGui() {
        auto uploadData = [this]{
            glm::mat4 translate = glm::translate(m_Translation);
            glm::mat4 rotate = glm::toMat4(glm::quat(m_Rotation));
            glm::mat4 scale = glm::scale(m_Scale);

            m_ModelDataStruct.model = translate * rotate * scale;
            m_ModelData->setData(&m_ModelDataStruct, sizeof(ModelData));
        };

        ImGui::Text("Transformation");
        if (ImGui::SliderFloat3("Translation", glm::value_ptr(m_Translation), -1.0f, 1.0f)){
            uploadData();
        }
        if (ImGui::SliderFloat3("Scale", glm::value_ptr(m_Scale), 0.0f, 2.0f)){
            uploadData();
        }
        if (ImGui::SliderFloat3("Rotation", glm::value_ptr(m_Rotation), 0.0f, 360.0f)){
            uploadData();
        }

        ImGui::NewLine();
        ImGui::Text("Mix");
        if (ImGui::SliderFloat("Mix", &m_MixDataStruct.mix, 0.0f, 1.0f)){
            m_MixData->setData(&m_MixDataStruct, sizeof(MixData));
        }
        if (ImGui::SliderFloat("Texture Count", &m_MixDataStruct.texOffset, 0.0f, 50.0f, "%.0f")){
            m_MixData->setData(&m_MixDataStruct, sizeof(MixData));
        }

    }
}