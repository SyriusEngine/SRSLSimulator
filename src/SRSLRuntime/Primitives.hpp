#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

namespace SrslRuntime{

    struct VertexInput{
        uint32_t SRV_VERTEX_ID;
        uint32_t SRV_INSTANCE_ID;
    };

    typedef std::unordered_map<std::string, glm::vec4> Vertex;
    typedef std::unordered_map<std::string, glm::vec4> Fragment;
}