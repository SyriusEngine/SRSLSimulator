#pragma once

#include "Shared/Layer.hpp"

namespace Simulator{

    class MVPLayer : public Layer{
    public:
        explicit MVPLayer(UP<Context>& context);

        void onRender() override;

        void onImGui() override;

    private:
        UP<VertexBuffer> m_VertexBuffer;
        UP<IndexBuffer> m_IndexBuffer;

        UP<ConstantBuffer> m_ModelData;
        ModelData m_ModelDataStruct;
        UP<ConstantBuffer> m_ProjectionData;
        ProjectionData m_ProjectionDataStruct;
        UP<ConstantBuffer> m_ViewData;
        ViewData m_ViewDataStruct;
        Camera m_Camera;


        UP<Shader> m_Shader;

        glm::vec3 m_Translation;
        glm::vec3 m_Scale;
        glm::vec3 m_Rotation;
    };

}