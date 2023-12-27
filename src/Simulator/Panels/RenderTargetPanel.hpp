#pragma once

#include "Panel.hpp"

namespace Simulator{

    class RenderTargetPanel: public Panel{
    public:
        explicit RenderTargetPanel(SimulatorStore& store);

        ~RenderTargetPanel() override = default;

        void draw() override;

    private:
        Syrius::ResourceView<Syrius::Texture2D> m_RenderTargetView;




    };

}