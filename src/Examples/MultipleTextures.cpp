#include "MultipleTextures.hpp"

namespace Simulator{

    MultipleTexturesLayer::MultipleTexturesLayer(UP<Context>& context):
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
                "./ExampleShaders/MultipleTextures-fs.srsl"
        );

        ImageDesc awesomeFaceDesc;
        awesomeFaceDesc.flipOnLoad = true;
        awesomeFaceDesc.path = "./Resources/Textures/awesomeface.png";
        m_AwesomeFace = m_Context->createTexture2D(awesomeFaceDesc);

        ImageDesc instagramLogoDesc;
        instagramLogoDesc.flipOnLoad = true;
        instagramLogoDesc.path = "./Resources/Textures/insta.png";
        m_InstagramLogo = m_Context->createTexture2D(instagramLogoDesc);
    }

    void MultipleTexturesLayer::onRender() {
        m_VertexBuffer->bind();
        m_IndexBuffer->bind();
        m_Shader->bind();
        m_AwesomeFace->bind(0);
        m_InstagramLogo->bind(1);
        m_Context->draw();
    }

    void MultipleTexturesLayer::onImGui() {

    }
}
