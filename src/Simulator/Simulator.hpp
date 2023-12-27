#pragma once

#include "SimulatorInclude.hpp"
#include "SimulatorStore.hpp"
#include "GraphicsAPI/Profiler.hpp"

#include "Renderer.hpp"

#include "Panels/NavBar.hpp"
#include "Panels/PipelinePanel.hpp"

namespace Simulator{

    class Simulator{
    public:
        explicit Simulator(const std::string& configFile);

        ~Simulator();

        void run();

    private:

        void drawImGui();

        void setupPanels();

    private:
        SimulatorStore m_Store;


    };
}