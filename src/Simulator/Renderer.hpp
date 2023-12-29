#pragma once

#include "SimulatorInclude.hpp"
#include "SimulatorStore.hpp"

namespace Simulator{

    class Renderer{
    public:
        explicit Renderer(SimulatorStore& store);

        ~Renderer() = default;

        void draw();

        void savePipelineConfig(const std::string& path);

        void loadPipelineConfig(const std::string& path);

        void loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    public:
        UP<VertexLayout> vertexLayout;
        UP<FrameBuffer> frameBuffer;
        UP<Shader> shader;

    private:
        SimulatorStore& m_Store;

        uint32 m_Width;
        uint32 m_Height;

        UP<Context> m_Context;


    };

}