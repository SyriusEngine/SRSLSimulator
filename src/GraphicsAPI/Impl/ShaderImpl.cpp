#include <fstream>
#include "ShaderImpl.hpp"
#include "Pipeline.hpp"
#include "../../../include/GraphicsAPI/Profiler.hpp"

namespace SrslAPI{

    ShaderImpl::ShaderImpl(const std::string &vertexShader, const std::string &fragmentShader,
                           const UP<Pipeline>& pipeline):
    Shader(vertexShader, fragmentShader),
    m_Pipeline(pipeline),
    m_ShaderModule(nullptr),
    m_VertexShaderEntry(nullptr),
    m_FragmentShaderEntry(nullptr){
        compileSrsl(vertexShader, fragmentShader);
        compileCpp();
    }

    ShaderImpl::~ShaderImpl() {
        unloadExecutable();
//        if (std::filesystem::exists(m_OutputPath)) {
//            std::filesystem::remove_all(m_OutputPath);
//        }
    }

    void ShaderImpl::bind() {
        if (m_ShaderModule == nullptr) {
            SIM_START_TIME("Shader::LoadExecutable");
            loadExecutable();
            SIM_STOP_TIME("Shader::LoadExecutable");
        }
        m_Pipeline->setShader(this);
    }

    void ShaderImpl::compileSrsl(const std::string &vertexShader, const std::string &fragmentShader) {
        m_VertexShaderModule = UP<Srsl::ShaderModule>(Srsl::createShaderModule(vertexShader));
        m_FragmentShaderModule = UP<Srsl::ShaderModule>(Srsl::createShaderModule(fragmentShader));
        m_ShaderProgram = UP<Srsl::ShaderProgram>(Srsl::createShaderProgram());
        m_ShaderProgram->addShaderModule(m_VertexShaderModule.get());
        m_ShaderProgram->addShaderModule(m_FragmentShaderModule.get());

        // check if output dir exists, if not create it
        m_OutputPath = std::filesystem::current_path();
        m_OutputPath /= "CompiledShaders";
        if(!std::filesystem::exists(m_OutputPath)){
            std::filesystem::create_directory(m_OutputPath);
        }
        Srsl::CppDescriptor cppDescriptor;
        cppDescriptor.outputFile = m_OutputPath.string() + "/" + COMPILED_SRSL_NAME;
        cppDescriptor.exportDebugInfo = true;
        m_ShaderProgram->exportCpp(cppDescriptor);
    }

    void ShaderImpl::compileCpp() {
        std::filesystem::path includePath = std::filesystem::current_path();
        includePath /= "Dependencies";
        includePath /= "glm";
        includePath /= "glm";
        if (!std::filesystem::exists(includePath)) {
            throw std::runtime_error("Dependencies folder not found. Please make sure that there exists a folder structure like this: \n"
                                     "Dependencies\n"
                                     "    glm\n"
                                     "        glm\n"
                                     "            glm.hpp\n"
                                     "In the same directory as this executable.\n"
                                     "The current dir is: " + includePath.string());
        }
        m_ExecutablePath = m_OutputPath.string();
        m_ExecutablePath += "/__shader__" + std::to_string(reinterpret_cast<uint64_t>(this)) + ".dll";

        std::string cmd = "g++ -g -shared -std=c++17 "; // shared flag for dll, -g for debug symbols
        cmd += "-I./Dependencies/glm ";
        cmd += "-o " + m_ExecutablePath + " ";
        cmd += m_OutputPath.string() + "/" + COMPILED_VS_NAME + " ";
        cmd += m_OutputPath.string() + "/" + COMPILED_FS_NAME + " ";

        auto result = system(cmd.c_str());
        if (result != 0) {
            throw std::runtime_error("Failed to compile shader (g++ exited with code " + std::to_string(result) + ")");
        }
    }

    void ShaderImpl::loadExecutable() {
        m_ShaderModule = LoadLibrary(m_ExecutablePath.c_str());
        if(m_ShaderModule == nullptr){
            throw std::runtime_error("Failed to load shader module");
        }
        m_VertexShaderEntry = reinterpret_cast<VertexShaderMain>(GetProcAddress(m_ShaderModule, "main__Vertex"));
        if (m_VertexShaderEntry == nullptr) {
            throw std::runtime_error("Failed to load vertex shader entry point");
        }
        m_FragmentShaderEntry = reinterpret_cast<FragmentShaderMain>(GetProcAddress(m_ShaderModule, "main__Fragment"));
        if (m_FragmentShaderEntry == nullptr) {
            throw std::runtime_error("Failed to load fragment shader entry point");
        }

    }

    void ShaderImpl::unloadExecutable() {
        if (m_ShaderModule != nullptr) {
            FreeLibrary(m_ShaderModule);
            m_ShaderModule = nullptr;
        }
    }

}