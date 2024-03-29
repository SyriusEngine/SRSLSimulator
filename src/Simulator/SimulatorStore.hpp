#pragma once

#include "SimulatorInclude.hpp"

namespace Simulator{

    typedef std::vector<std::vector<float>> UIVertex;
    typedef std::unordered_map<uint32, std::vector<uint32>> ShaderLineInfo;

    struct TextureStorage{
        std::string path;
        uint32 slot;
        bool flipOnLoad;
    };

    class Panel;
    class Renderer;

    class SimulatorStore{
    public:
        explicit SimulatorStore(const std::string& configFile);

        ~SimulatorStore();

    public:
        EasyIni::Configuration config;

        Syrius::Resource<Syrius::SyriusWindow> window;
        Syrius::ResourceView<Syrius::Context> srContext;

        UP<Renderer> renderer;

        UP<Panel> navBar;
        UP<Panel> pipelinePanel;
        UP<Panel> renderTargetPanel;
        UP<Panel> vertexShaderPanel;
        UP<Panel> fragmentShaderPanel;

        std::string vertexShaderPath;
        std::string fragmentShaderPath;

        std::string projectPath;

        std::vector<UIVertex> vertices;
        std::vector<uint32> indices;

        std::vector<TextureStorage> textures;

        ShaderLineInfo vertexShaderLineInfo;
        ShaderLineInfo fragmentShaderLineInfo;
        std::string compiledVertexShaderPath;
        std::string compiledFragmentShaderPath;

    };

}