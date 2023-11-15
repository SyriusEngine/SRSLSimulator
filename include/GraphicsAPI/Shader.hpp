#pragma once

#include "Include.hpp"

namespace SrslAPI{

    class SRSL_GRAPHICS_API Shader{
    public:
        Shader(const std::string& vertexShader, const std::string& fragmentShader);

        virtual ~Shader();

        virtual void bind() = 0;

    };
}