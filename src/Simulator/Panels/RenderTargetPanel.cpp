#include "RenderTargetPanel.hpp"

namespace Simulator{

    RenderTargetPanel::RenderTargetPanel(SimulatorStore &store):
    Panel(store, "RenderTarget", 2 * store.window->getWidth() / 5, store.window->getHeight() - store.navBar->panelHeight, store.pipelinePanel->panelWidth, store.navBar->panelHeight){

        Syrius::Texture2DDesc desc;
        desc.width = DRAW_WIDTH;
        desc.height = DRAW_HEIGHT;
        desc.format = SR_TEXTURE_RGBA_UI8;
        desc.data = nullptr;
        m_RenderTargetView = m_Store.srContext->createTexture2D(desc);

    }

    void RenderTargetPanel::draw() {
        panelX = m_Store.pipelinePanel->panelWidth;
        onBeginDraw();
        if (ImGui::Button("Render")){
            m_Store.renderer->draw();
            const auto& data = m_Store.renderer->frameBuffer->getColorAttachment(0)->getData();
            m_RenderTargetView->setData(data.data(), 0, 0, DRAW_WIDTH, DRAW_HEIGHT);
        }

        ImGui::Image((void*)m_RenderTargetView->getIdentifier(), ImVec2(DRAW_WIDTH, DRAW_HEIGHT), ImVec2(0, 1), ImVec2(1, 0));

        onEndDraw();
    }
}