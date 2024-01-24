#pragma once

#include "Include.hpp"

namespace Simulator{

    class Layer{
    public:
        explicit Layer(UP<Context>& context);

        virtual ~Layer() = default;

        virtual void onRender() = 0;

        virtual void onImGui() = 0;

    protected:
        UP<Context>& m_Context;
        UP<VertexLayout> m_VertexLayout;
    };

}