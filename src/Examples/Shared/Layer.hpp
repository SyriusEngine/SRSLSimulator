#pragma once

#include "Include.hpp"

namespace Simulator{

    class Layer{
    public:
        explicit Layer(UP<Context>& context): m_Context(context){}

        virtual ~Layer() = default;

        virtual void onRender() = 0;

    protected:
        UP<Context>& m_Context;
    };

}