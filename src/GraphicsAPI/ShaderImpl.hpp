#pragma once

#include "../../include/GraphicsAPI/Shader.hpp"
#include "../../SyriusShadingLanguage/include/SrslCompiler.hpp"
#include <filesystem>
#include <windows.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Primitives.hpp"
#include "VideoMemory.hpp"

#define COMPILED_SRSL_NAME "comp.cpp"
#define COMPILED_VS_NAME "comp-vs.cpp"
#define COMPILED_FS_NAME "comp-fs.cpp"

namespace SrslAPI{

    typedef std::unordered_map<std::string, glm::vec4> (*VertexShaderMain)(const std::unordered_map<std::string, char*>&, VideoMemory*);
    typedef std::unordered_map<std::string, glm::vec4> (*FragmentShaderMain)(const std::unordered_map<std::string, glm::vec4>&, VideoMemory*);

    class Pipeline;

    class ShaderImpl: public Shader{
    public:
        ShaderImpl(const std::string& vertexShader, const std::string& fragmentShader,
                   const UP<Pipeline>& pipeline, const UP<VideoMemory>& videoMemory);

        ~ShaderImpl() override;

        void bind() override;

        inline OutputVertex executeVertexShader(InputVertex& input){
            return m_VertexShaderEntry(input, m_VideoMemory.get());
        }

        inline OutputFragment executeFragmentShader(const InputFragment& input){
            return m_FragmentShaderEntry(input, m_VideoMemory.get());
        }

    private:

        void compileSrsl(const std::string& vertexShader, const std::string& fragmentShader);

        void compileCpp();

        void loadExecutable();

        void unloadExecutable();

        void writeVideoMemoryHeader();

    private:
        const UP<Pipeline>& m_Pipeline;
        const UP<VideoMemory>& m_VideoMemory;

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