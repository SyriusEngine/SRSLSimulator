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
#define DRAW_HEIGHT 600

namespace Simulator{

    struct Vertex{
        float x, y, z;
        float r, g, b;
        float nx, ny, nz;
        float u, v, w, q;
    };

    using namespace SrslAPI;

    inline SRSL_SCALAR_TYPE cCountToType(uint32 count){
        switch (count) {
            case 1: return SRSL_FLOAT32_1;
            case 2: return SRSL_FLOAT32_2;
            case 3: return SRSL_FLOAT32_3;
            case 4: return SRSL_FLOAT32_4;
            default: return SRSL_FLOAT32_4;
        }
    }

}