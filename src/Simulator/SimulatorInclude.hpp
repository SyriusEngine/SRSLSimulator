#pragma once

#include <SyriusCore/SyriusCore.hpp>
#include <GraphicsAPI/SrslAPI.hpp>
#include <nlohmann/json.hpp>
#include <EasyIni/EasyIni.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

#define SIM_WIDTH 1920
#define SIM_HEIGHT 1080

#define DRAW_WIDTH 800
#define DRAW_HEIGHT 800

namespace Simulator{

    struct Vertex{
        float x, y, z;
        float r, g, b;
        float nx, ny, nz;
        float u, v, w, q;
    };

    using namespace SrslAPI;

}