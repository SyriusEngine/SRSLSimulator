#pragma once

#include <SyriusCore/SyriusCore.hpp>
#include <GraphicsAPI/SrslAPI.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

#define SIM_WIDTH 1280
#define SIM_HEIGHT 780

namespace Simulator{

    struct Vertex{
        float x, y, z;
        float r, g, b;
        float nx, ny, nz;
        float u, v, w, q;
    };

    using namespace SrslAPI;

}