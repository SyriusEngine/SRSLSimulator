#pragma once

#include "../../include/GraphicsAPI/Include.hpp"
#include <glm/glm.hpp>

namespace SrslAPI{

    typedef std::unordered_map<std::string, char*> InputVertex;
    typedef std::unordered_map<uint32_t, char*> ConstantBuffers;

    typedef std::unordered_map<std::string, glm::vec4> OutputVertex;

    typedef OutputVertex InputFragment;

    typedef OutputVertex OutputFragment;

}