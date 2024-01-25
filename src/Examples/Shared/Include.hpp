#pragma once

#include <SyriusCore/SyriusCore.hpp>
#include <GraphicsAPI/SrslAPI.hpp>
#include <EasyIni/EasyIni.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/quaternion.hpp>
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

    struct ModelData{
        glm::mat4 model = glm::mat4(1.0f);
    };

    struct MixData{
        float mix = 0.5f;
        float texOffset = 1.0f;
        float padding[2]{};
    };

    struct ProjectionData{
        glm::mat4 projection = glm::mat4(1.0f);
    };

    struct ViewData{
        glm::mat4 view = glm::mat4(1.0f);
    };

    struct Camera{
        glm::vec3 position = {3.50f, 3.50f, 5.50f};
        glm::vec3 front = {-0.50f, -0.42f, -0.74f};
        glm::vec3 up = {-0.24f, 0.91f, -0.35f};
        glm::vec3 right = {0.82f, 0.00f, -0.57f};
        glm::vec3 worldUp = {0.00f, 1.00f, 0.00f};
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

    static Vertex s_CubeVertices[] = {
        // Front
        {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 0.f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        // Back
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 0.f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},

        // Left
        {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        // Right
        {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

        // Top
        {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 0.f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 0.f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

        // Bottom
        {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.5f}, {0.0f, 1.0f, 0.f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
    };

    static uint32 s_CubeIndices[] = {
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 5, 6,
        6, 7, 4,

        // Left
        8, 9, 10,
        10, 11, 8,

        // Right
        12, 13, 14,
        14, 15, 12,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 21, 22,
        22, 23, 20
    };
}