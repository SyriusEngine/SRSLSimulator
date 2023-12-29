#pragma once

#include "Panel.hpp"

namespace Simulator{

    class PipelinePanel: public Panel{
    public:
        explicit PipelinePanel(SimulatorStore& store);

        ~PipelinePanel() override = default;

        void draw() override;

    private:
        void drawVertexLayout();

        void drawMesh();

        void drawShaders();
    };

}