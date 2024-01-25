#include "MVP.hpp"

namespace Simulator{

    MVPLayer::MVPLayer(UP<Context> &context) :
    Layer(context) {
        m_VertexBuffer = m_Context->createVertexBuffer(
                m_VertexLayout,
                s_CubeVertices,
                sizeof(s_CubeVertices)
        );
        m_IndexBuffer = m_Context->createIndexBuffer(
                s_CubeIndices,
                36
        );
        m_Shader = m_Context->createShader(
                "./ExampleShaders/MVP-vs.srsl",
                "./ExampleShaders/MVP-fs.srsl"
        );

        m_ProjectionDataStruct.projection = glm::perspective(
                glm::radians(45.0f),
                800.0f / 600.0f,
                0.1f,
                100.0f
        );

        // calculate view matrix
        m_ViewDataStruct.view = glm::lookAt(
                m_Camera.position,
                m_Camera.position + m_Camera.front,
                m_Camera.up
        );

        ConstantBufferDesc projectionDataDesc;
        projectionDataDesc.size = sizeof(ProjectionData);
        projectionDataDesc.data = &m_ProjectionDataStruct;
        projectionDataDesc.slot = 0;
        projectionDataDesc.name = "ProjectionData";
        m_ProjectionData = m_Context->createConstantBuffer(projectionDataDesc);

        ConstantBufferDesc viewDataDesc;
        viewDataDesc.size = sizeof(ViewData);
        viewDataDesc.data = &m_ViewDataStruct;
        viewDataDesc.slot = 1;
        viewDataDesc.name = "ViewData";
        m_ViewData = m_Context->createConstantBuffer(viewDataDesc);

        ConstantBufferDesc modelDataDesc;
        modelDataDesc.size = sizeof(ModelData);
        modelDataDesc.data = &m_ModelDataStruct;
        modelDataDesc.slot = 2;
        modelDataDesc.name = "ModelData";
        m_ModelData = m_Context->createConstantBuffer(modelDataDesc);

    }

    void MVPLayer::onRender() {
        m_VertexBuffer->bind();
        m_IndexBuffer->bind();

        m_Shader->bind();

        m_ModelData->bind();
        m_ProjectionData->bind();
        m_ViewData->bind();

        m_Context->draw();
    }

    void MVPLayer::onImGui() {

    }
}