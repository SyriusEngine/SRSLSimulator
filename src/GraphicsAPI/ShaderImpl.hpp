#pragma once

#include "../../include/GraphicsAPI/Shader.hpp"
#include "../../SyriusShadingLanguage/include/SrslCompiler.hpp"
#include <filesystem>
#include <windows.h>

#define COMPILED_SRSL_NAME "comp.cpp"
#define COMPILED_VS_NAME "comp-vs.cpp"
#define COMPILED_FS_NAME "comp-fs.cpp"

namespace SrslAPI{

    class Pipeline;

    class ShaderImpl: public Shader{
    public:
        ShaderImpl(const std::string& vertexShader, const std::string& fragmentShader, Pipeline* pipeline);

        ~ShaderImpl() override;

        void bind() override;

    private:

        void compileSrsl(const std::string& vertexShader, const std::string& fragmentShader);

        void compileCpp();

        void loadExecutable();

        void unloadExecutable();

    private:
        Pipeline* m_Pipeline;
        UP<Srsl::ShaderModule> m_VertexShaderModule;
        UP<Srsl::ShaderModule> m_FragmentShaderModule;
        UP<Srsl::ShaderProgram> m_ShaderProgram;

        std::filesystem::path m_OutputPath;
        std::string m_ExecutablePath;

        HMODULE m_ShaderModule;



    };
}