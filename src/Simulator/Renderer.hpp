#pragma once

#include "SimulatorInclude.hpp"
#include "SimulatorStore.hpp"

namespace Simulator{

    class Renderer{
    public:
        explicit Renderer(SimulatorStore& store);

        ~Renderer() = default;

        void draw();

    public:
        UP<VertexLayout> vertexLayout;

    private:
        SimulatorStore& m_Store;

        uint32 m_Width;
        uint32 m_Height;

        UP<Context> m_Context;
        UP<FrameBuffer> m_FrameBuffer;


    };

}