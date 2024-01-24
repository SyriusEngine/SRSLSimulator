#pragma once

#include "Shared/Layer.hpp"

namespace Simulator{

    struct ModelData{
        glm::mat4 model = glm::mat4(1.0f);
    };

    struct MixData{
        float mix = 0.5f;
        float padding[3]{};
    };

    class ConstantBufferLayer : public Layer{
    public:
        explicit ConstantBufferLayer(UP<Context>& context);

        void onRender() override;

        void onImGui() override;

    private:
        UP<VertexBuffer> m_VertexBuffer;
        UP<IndexBuffer> m_IndexBuffer;

        UP<Texture2D> m_AwesomeFace;
        UP<Texture2D> m_InstagramLogo;

        UP<ConstantBuffer> m_MixData;
        MixData m_MixDataStruct;
        UP<ConstantBuffer> m_ModelData;
        ModelData m_ModelDataStruct;

        UP<Shader> m_Shader;

        glm::vec3 m_Translation;
        glm::vec3 m_Scale;
        glm::vec3 m_Rotation;
    };

}