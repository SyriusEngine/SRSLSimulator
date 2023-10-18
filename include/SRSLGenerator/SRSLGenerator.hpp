#pragma once

#include "SRSLGeneratorInclude.hpp"

namespace SrslGenerator{

    struct SRSL_GEN_API GeneratorDesc{
        std::string vertexShaderPath;
        std::string fragmentShaderPath;
        bool exportASTAsDot = false;
        bool exportSymbolTableAsHtml = false;
    };

    void generateExecutable(const GeneratorDesc& desc);

}

