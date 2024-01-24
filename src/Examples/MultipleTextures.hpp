#pragma once

#include "Shared/Layer.hpp"

namespace Simulator{

    class MultipleTexturesLayer : public Layer{
    public:
        explicit MultipleTexturesLayer(UP<Context>& context);

        void onRender() override;

        void onImGui() override;

    private:
        UP<VertexBuffer> m_VertexBuffer;
        UP<IndexBuffer> m_IndexBuffer;
        UP<Texture2D> m_AwesomeFace;
        UP<Texture2D> m_InstagramLogo;
        UP<Shader> m_Shader;
    };

}