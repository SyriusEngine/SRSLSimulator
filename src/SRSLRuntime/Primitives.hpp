#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

namespace SrslRuntime{

    static const uint32_t s_ImageWidth = 800;
    static const uint32_t s_ImageHeight = 600;

    struct VertexInput{
        uint32_t SRV_VERTEX_ID;
        uint32_t SRV_INSTANCE_ID;
    };

    typedef std::unordered_map<std::string, glm::vec4> Vertex;
    typedef std::unordered_map<std::string, glm::vec4> Fragment;
}