#pragma once

#include "Shared/Layer.hpp"

namespace Simulator{

    class InterpolationLayer : public Layer{
    public:
        explicit InterpolationLayer(UP<Context>& context);

        void onRender() override;

        void onImGui() override;

    private:
        UP<VertexBuffer> m_VertexBuffer;
        UP<IndexBuffer> m_IndexBuffer;
        UP<Texture2D> m_Texture;
        UP<Shader> m_Shader;


    };

}