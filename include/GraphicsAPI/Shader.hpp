#pragma once

#include "Include.hpp"

namespace SrslAPI{

    struct SRSL_GRAPHICS_API ShaderDebugInfo{
        std::string vertexShaderSource;
        std::string vertexShaderCppSource;
        std::string vertexShaderLineInfo;

        std::string fragmentShaderSource;
        std::string fragmentShaderCppSource;
        std::string fragmentShaderLineInfo;
    };

    class SRSL_GRAPHICS_API Shader{
    public:
        Shader(const std::string& vertexShader, const std::string& fragmentShader);

        virtual ~Shader();

        virtual void bind() = 0;

        [[nodiscard]] inline const ShaderDebugInfo& getDebugInfo() const{
            return m_DebugInfo;
        }

    protected:
        ShaderDebugInfo m_DebugInfo;

    };
}