#pragma once

#include <SyriusCore/SyriusCore.hpp>
#include <GraphicsAPI/SrslAPI.hpp>
#include <EasyIni/EasyIni.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

#define DEF_WINDOW_WIDTH 1280
#define DEF_WINDOW_HEIGHT 720

#define DEF_FRAMEBUFFER_WIDTH 800
#define DEF_FRAMEBUFFER_HEIGHT 600

namespace Simulator{

    using namespace SrslAPI;

    struct Vertex{
        glm::vec3 position;
        glm::vec3 color;
        glm::vec3 normal;
        glm::vec2 texCoord;
    };

    static Vertex s_RectangleVertices[] = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
    };

    static uint32 s_RectangleIndices[] = {
        0, 1, 2,
        2, 3, 0
    };
}