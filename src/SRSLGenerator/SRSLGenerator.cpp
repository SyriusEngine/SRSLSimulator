#include "../../include/SRSLGenerator/SRSLGenerator.hpp"

namespace SrslGenerator{

    using namespace Srsl;

    void compileProgram(const GeneratorDesc& desc){
        auto vsm = createShaderModule(desc.vertexShaderPath);
        if(desc.exportASTAsDot){
            vsm->exportAstDot("VSM.dot");
        }
        if(desc.exportSymbolTableAsHtml){
            vsm->exportSymbolTableHtml("VSM.html");
        }

        auto fsm = createShaderModule(desc.fragmentShaderPath);
        if(desc.exportASTAsDot){
            fsm->exportAstDot("FSM.dot");
        }
        if(desc.exportSymbolTableAsHtml){
            fsm->exportSymbolTableHtml("FSM.html");
        }

        auto program = createShaderProgram();
        program->addShaderModule(vsm);
        program->addShaderModule(fsm);
        program->link();

        CppDescriptor cppDesc;
        cppDesc.outputFile = "./src/SRSLRuntime/Shader/comp.cpp";
        program->exportCpp(cppDesc);

        delete program;
    }

    std::string generateCommand(){
        std::string base = "g++ ";
        std::string glmInclude = "-I./Dependencies ";
        std::string outputLocation = "-o ./cmake-build-debug/SRSLRuntime.exe ";

        std::string sourceFiles = "./src/SRSLRuntime/Shader/comp-vs.cpp ";
        sourceFiles += "./src/SRSLRuntime/Shader/comp-fs.cpp ";


        return base + glmInclude + outputLocation + sourceFiles;
    }

    void generateExecutable(const GeneratorDesc& desc){
        compileProgram(desc);
        auto cmd = generateCommand();
        system(cmd.c_str());
    }
}