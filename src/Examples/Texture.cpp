#include "Texture.hpp"

namespace Simulator{

    TextureLayer::TextureLayer(UP<Context>& context):
            Layer(context){
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
                "./ExampleShaders/Rectangle-vs.srsl",
                "./ExampleShaders/Texture-fs.srsl"
        );

        ImageDesc t2dDesc;
        t2dDesc.flipOnLoad = true;
        t2dDesc.path = "./Resources/Textures/awesomeface.png";
        m_Texture = m_Context->createTexture2D(t2dDesc);
    }

    void TextureLayer::onRender() {
        m_VertexBuffer->bind();
        m_IndexBuffer->bind();
        m_Shader->bind();
        m_Texture->bind(0);
        m_Context->draw();
    }

    void TextureLayer::onImGui() {

    }
}