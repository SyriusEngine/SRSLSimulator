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

    typedef std::unordered_map<std::string, glm::vec4> (*VertexShaderMain)(const std::unordered_map<std::string, char*>&, std::unordered_map<uint32_t, char*>&);
    typedef std::unordered_map<std::string, glm::vec4> (*FragmentShaderMain)(const std::unordered_map<std::string, glm::vec4>&, std::unordered_map<uint32_t, char*>&);

    class Pipeline;

    class ShaderImpl: public Shader{
    public:
        ShaderImpl(const std::string& vertexShader, const std::string& fragmentShader,
                   const UP<Pipeline>& pipeline);

        ~ShaderImpl() override;

        void bind() override;

        inline OutputVertex executeVertexShader(InputVertex& input, ConstantBuffers& cbs){
            return m_VertexShaderEntry(input, cbs);
        }

        inline OutputFragment executeFragmentShader(const InputFragment& input, ConstantBuffers& cbs){
            return m_FragmentShaderEntry(input, cbs);
        }

    private:

        void compileSrsl(const std::string& vertexShader, const std::string& fragmentShader);

        void compileCpp();

        void loadExecutable();

        void unloadExecutable();

    private:
        const UP<Pipeline>& m_Pipeline;

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