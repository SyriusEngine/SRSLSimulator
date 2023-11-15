#include "ShaderImpl.hpp"
#include "Pipeline.hpp"

namespace SrslAPI{

    ShaderImpl::ShaderImpl(const std::string &vertexShader, const std::string &fragmentShader, Pipeline *pipeline):
    Shader(vertexShader, fragmentShader),
    m_Pipeline(pipeline),
    m_ShaderModule(nullptr){
        compileSrsl(vertexShader, fragmentShader);
        compileCpp();
    }

    ShaderImpl::~ShaderImpl() {
        unloadExecutable();
    }

    void ShaderImpl::bind() {
        if (m_ShaderModule == nullptr) {
            loadExecutable();
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
        m_ShaderProgram->exportCpp(cppDescriptor);
    }

    void ShaderImpl::compileCpp() {
        std::filesystem::path includePath = std::filesystem::current_path();
        includePath /= "Dependencies";
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

        std::string cmd = "g++ -shared "; // shared flag for dll
        cmd += "-I./Dependencies ";
        cmd += "-o " + m_ExecutablePath + " ";
        cmd += m_OutputPath.string() + "/" + COMPILED_VS_NAME + " ";
        cmd += m_OutputPath.string() + "/" + COMPILED_FS_NAME + " ";

        system(cmd.c_str());
    }

    void ShaderImpl::loadExecutable() {
        m_ShaderModule = LoadLibrary(m_ExecutablePath.c_str());
        if(m_ShaderModule == nullptr){
            throw std::runtime_error("Failed to load shader module");
        }

    }

    void ShaderImpl::unloadExecutable() {
        if (m_ShaderModule != nullptr) {
            FreeLibrary(m_ShaderModule);
            m_ShaderModule = nullptr;
        }
    }
}