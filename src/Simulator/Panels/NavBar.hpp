#pragma once

#include "Panel.hpp"

namespace Simulator{

    class NavBar: public Panel{
    public:
        explicit NavBar(SimulatorStore& store);

        ~NavBar() override = default;

        void draw() override;
    };

}