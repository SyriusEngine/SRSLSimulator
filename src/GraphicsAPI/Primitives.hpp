#pragma once

#include "../../include/GraphicsAPI/Include.hpp"
#include <glm/glm.hpp>

namespace SrslAPI{

    const uint64_t MAX_CONSTANT_BUFFER_COUNT = 32;
    const uint64_t MAX_TEXTURE_COUNT = 32;
    const uint64_t MAX_SAMPLER_COUNT = 32;

    typedef std::unordered_map<std::string, char*> InputVertex;
    typedef std::unordered_map<std::string, glm::vec4> OutputVertex;

    typedef OutputVertex InputFragment;

    typedef OutputVertex OutputFragment;

    typedef std::vector<char*> ConstantBuffers;
    typedef std::vector<char*> Textures;
    typedef std::vector<char*> Samplers;

}