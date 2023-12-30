#pragma once

#include "SimulatorInclude.hpp"

namespace Simulator{

    typedef std::vector<std::vector<float>> UIVertex;

    class Panel;
    class Renderer;

    class SimulatorStore{
    public:
        explicit SimulatorStore(const std::string& configFile);

        ~SimulatorStore();

    public:
        EasyIni::Configuration config;

        Syrius::Resource<Syrius::Window> window;
        Syrius::ResourceView<Syrius::Context> srContext;

        UP<Renderer> renderer;

        UP<Panel> navBar;
        UP<Panel> pipelinePanel;
        UP<Panel> renderTargetPanel;
        UP<Panel> vertexShaderPanel;
        UP<Panel> fragmentShaderPanel;

        std::string vertexShaderPath;
        std::string fragmentShaderPath;

        std::vector<UIVertex> vertices;
        std::vector<uint32> indices;

    };

}