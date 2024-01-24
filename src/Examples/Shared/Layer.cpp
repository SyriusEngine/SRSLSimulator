#include "Layer.hpp"

namespace Simulator{

    Layer::Layer(UP<Context>& context):
    m_Context(context){
        m_VertexLayout = m_Context->createVertexLayout();
        m_VertexLayout->pushAttribute("Position", SRSL_FLOAT32_3);
        m_VertexLayout->pushAttribute("Color", SRSL_FLOAT32_3);
        m_VertexLayout->pushAttribute("Normal", SRSL_FLOAT32_3);
        m_VertexLayout->pushAttribute("TexCoord", SRSL_FLOAT32_2);
    }

}
