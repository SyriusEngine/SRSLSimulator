#include "Interpolation.hpp"

namespace Simulator{

    InterpolationLayer::InterpolationLayer(UP<Context>& context):
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
                "./ExampleShaders/Interpolation-fs.srsl"
                );


    }

    void InterpolationLayer::onRender() {
        m_VertexBuffer->bind();
        m_IndexBuffer->bind();
        m_Shader->bind();
        m_Context->draw();
    }

    void InterpolationLayer::onImGui() {

    }
}