#pragma once

#include "Panel.hpp"

namespace Simulator{

    class ShaderPanel: public Panel{
    public:
        ShaderPanel(SimulatorStore& store, const std::string& name, uint32 xPos);

        ~ShaderPanel() override = default;

        void draw() override;

        void loadShader(const std::string& shaderPath);

    private:
        std::string m_ShaderSource;
    };
}