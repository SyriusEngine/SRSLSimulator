#pragma once

#include "../SimulatorStore.hpp"

namespace Simulator{

    class Panel{
    public:
        Panel(SimulatorStore& store, const std::string& name, uint32 width, uint32 height, uint32 x = 0, uint32 y = 0);

        virtual ~Panel() = default;

        virtual void draw() = 0;

    public:
        uint32 panelWidth = 0;
        uint32 panelHeight = 0;
        uint32 panelX = 0;
        uint32 panelY = 0;

        std::string name;

    protected:

        void onBeginDraw();

        void onEndDraw();

    protected:
        SimulatorStore& m_Store;
    };

}