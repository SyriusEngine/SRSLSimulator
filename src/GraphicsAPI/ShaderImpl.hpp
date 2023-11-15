#pragma once

#include "../../include/GraphicsAPI/Shader.hpp"
#include "../../SyriusShadingLanguage/include/SrslCompiler.hpp"
#include <filesystem>
#include <windows.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Primitives.hpp"

#define COMPILED_SRSL_NAME "comp.cpp"
#define COMPILED_VS_NAME "comp-vs.cpp"
#define COMPILED_FS_NAME "comp-fs.cpp"

namespace SrslAPI{

    typedef std::unordered_map<std::string, glm::vec4> (*VertexShaderMain)(const std::unordered_map<std::string, char*>&);
    typedef glm::vec4 (*FragmentShaderMain)(const std::unordered_map<std::string, glm::vec4>&);

    class Pipeline;

    class ShaderImpl: public Shader{
    public:
        ShaderImpl(const std::string& vertexShader, const std::string& fragmentShader, Pipeline* pipeline);

        ~ShaderImpl() override;

        void bind() override;

        inline OutputVertex executeVertexShader(InputVertex& input){
            return m_VertexShaderEntry(input);
        }

        inline glm::vec4 executeFragmentShader(const InputFragment& input){
            return m_FragmentShaderEntry(input);
        }

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

        VertexShaderMain m_VertexShaderEntry;
        FragmentShaderMain m_FragmentShaderEntry;



    };
}