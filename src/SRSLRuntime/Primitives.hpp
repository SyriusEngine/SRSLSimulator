#pragma once

#include <glm/glm.hpp>

namespace SrslRuntime{

    struct VertexInput{
        uint32_t SRV_VERTEX_ID;
        uint32_t SRV_INSTANCE_ID;
    };

    struct VertexOutput{
        glm::vec<4, float> SRV_POSITION;
        float SRV_FRAG_DEPTH;
    };

    // vertex shader output and fragment shader input are the same
    typedef VertexOutput FragmentInput;

    struct FragmentOutput{
        glm::vec<4, float> SRV_TARGET_0;
        glm::vec<4, float> SRV_TARGET_1;
        glm::vec<4, float> SRV_TARGET_2;
        glm::vec<4, float> SRV_TARGET_3;
        glm::vec<4, float> SRV_TARGET_4;
        glm::vec<4, float> SRV_TARGET_5;
        glm::vec<4, float> SRV_TARGET_6;
        glm::vec<4, float> SRV_TARGET_7;
        glm::vec<4, float> SRV_TARGET_8;
        glm::vec<4, float> SRV_TARGET_9;
        glm::vec<4, float> SRV_TARGET_10;
        glm::vec<4, float> SRV_TARGET_11;
        glm::vec<4, float> SRV_TARGET_12;
        glm::vec<4, float> SRV_TARGET_13;
        glm::vec<4, float> SRV_TARGET_14;
        glm::vec<4, float> SRV_TARGET_15;

    };
}