#include "Renderer.hpp"

namespace Simulator{

    Renderer::Renderer(SimulatorStore &store):
    m_Store(store) {
        m_Context = createContext();

        m_Width = m_Store.config["Simulation"]["SimulationWidth"].getOrDefault<uint32>(DRAW_WIDTH);
        m_Height = m_Store.config["Simulation"]["SimulationHeight"].getOrDefault<uint32>(DRAW_HEIGHT);

        ColorAttachmentDesc caDesc;
        caDesc.width = m_Width;
        caDesc.height = m_Height;
        caDesc.channelCount = 4;
        caDesc.clearColor[0] = 0.8f;
        caDesc.clearColor[1] = 0.7f;
        caDesc.clearColor[2] = 0.3f;
        caDesc.clearColor[3] = 1.0f;

        FrameBufferLayout fbLayout;
        fbLayout.setViewport(m_Width, m_Height, 0, 0);
        fbLayout.addColorAttachment(caDesc);

        m_FrameBuffer = m_Context->createFrameBuffer(fbLayout);
        m_FrameBuffer->getColorAttachment(0)->clear();

        vertexLayout = m_Context->createVertexLayout();
    }

    void Renderer::draw() {
        m_FrameBuffer->getColorAttachment(0)->clear();
    }
}