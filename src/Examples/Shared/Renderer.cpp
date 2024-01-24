#include "Renderer.hpp"

namespace Simulator{

    Renderer::Renderer(EasyIni::Configuration &config):
    m_Config(config),
    m_Context(createContext()),
    m_RenderThread(){
        auto fbWidth = m_Config["Renderer"]["FrameBufferWidth"].getOrDefault<uint32>(DEF_FRAMEBUFFER_WIDTH);
        auto fbHeight = m_Config["Renderer"]["FrameBufferHeight"].getOrDefault<uint32>(DEF_FRAMEBUFFER_HEIGHT);
        auto clearColor = m_Config["Renderer"]["ClearColor"].getVectorOrDefault<float>({0.2f, 0.3f, 0.8f, 1.0f});

        ColorAttachmentDesc caDesc;
        caDesc.width = fbWidth;
        caDesc.height = fbHeight;
        caDesc.channelCount = 4;
        caDesc.clearColor[0] = clearColor[0];
        caDesc.clearColor[1] = clearColor[1];
        caDesc.clearColor[2] = clearColor[2];
        caDesc.clearColor[3] = clearColor[3];

        FrameBufferLayout fbLayout;
        fbLayout.setViewport(fbWidth, fbHeight, 0, 0);
        fbLayout.addColorAttachment(caDesc);

        m_FrameBuffer = m_Context->createFrameBuffer(fbLayout);

    }

    void Renderer::render() {
        m_RenderThread.addTask([this]{
            m_FrameBuffer->getColorAttachment(0)->clear();
            m_FrameBuffer->bind();
            for (auto& layer: m_Layers){
                layer->onRender();
            }
        });

    }

    uint32 Renderer::getFrameBufferWidth() const {
        return m_FrameBuffer->getColorAttachment(0)->getWidth();
    }

    uint32 Renderer::getFrameBufferHeight() const {
        return m_FrameBuffer->getColorAttachment(0)->getHeight();
    }

    const std::vector<uint8_t> &Renderer::getFrameBufferImage() const {
        return m_FrameBuffer->getColorAttachment(0)->getData();
    }

    void Renderer::clear() {
        m_FrameBuffer->getColorAttachment(0)->clear();
    }
}
