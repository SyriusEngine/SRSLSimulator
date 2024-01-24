#include "Renderer.hpp"

namespace Simulator{

    Renderer::Renderer(EasyIni::Configuration &config):
    m_Config(config),
    m_Context(createContext()),
    m_RenderThread(){
        auto fbWidth = m_Config["Renderer"]["FrameBufferWidth"].getOrDefault<uint32>(DEF_FRAMEBUFFER_WIDTH);
        auto fbHeight = m_Config["Renderer"]["FrameBufferHeight"].getOrDefault<uint32>(DEF_FRAMEBUFFER_HEIGHT);

        ColorAttachmentDesc caDesc;
        caDesc.width = fbWidth;
        caDesc.height = fbHeight;
        caDesc.channelCount = 4;
        caDesc.clearColor[0] = m_Config["Renderer"]["ClearColorR"].getOrDefault<float>(0.2f);
        caDesc.clearColor[1] = m_Config["Renderer"]["ClearColorG"].getOrDefault<float>(0.3f);
        caDesc.clearColor[2] = m_Config["Renderer"]["ClearColorB"].getOrDefault<float>(0.8f);
        caDesc.clearColor[3] = m_Config["Renderer"]["ClearColorA"].getOrDefault<float>(1.0f);

        FrameBufferLayout fbLayout;
        fbLayout.setViewport(fbWidth, fbHeight, 0, 0);
        fbLayout.addColorAttachment(caDesc);

        m_FrameBuffer = m_Context->createFrameBuffer(fbLayout);

    }

    Renderer::~Renderer() {
        m_RenderThread.stop();

        m_Config["Renderer"]["FrameBufferWidth"] = getFrameBufferWidth();
        m_Config["Renderer"]["FrameBufferHeight"] = getFrameBufferHeight();
        auto clearColor = m_FrameBuffer->getColorAttachment(0)->getClearColor();
        m_Config["Renderer"]["ClearColorR"] = clearColor[0];
        m_Config["Renderer"]["ClearColorG"] = clearColor[1];
        m_Config["Renderer"]["ClearColorB"] = clearColor[2];
        m_Config["Renderer"]["ClearColorA"] = clearColor[3];
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

    void Renderer::save(const std::string &path) {
        m_FrameBuffer->getColorAttachment(0)->save(path);
    }

    void Renderer::renderImGui() {
        for (auto& layer: m_Layers){
            layer->onImGui();
        }
    }

    float *Renderer::getClearColor() {
        return m_FrameBuffer->getColorAttachment(0)->getClearColor();
    }
}
