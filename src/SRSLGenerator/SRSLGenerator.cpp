#include "../../include/SRSLGenerator/SRSLGenerator.hpp"

namespace SrslGenerator{

    using namespace Srsl;

    void compileProgram(const GeneratorDesc& desc){
        auto vsm = createShaderModule(desc.vertexShaderPath);
        if(desc.exportASTAsDot){
            vsm->exportAstDot(desc.outputDirectory + "/VSM.dot");
        }
        if(desc.exportSymbolTableAsHtml){
            vsm->exportSymbolTableHtml(desc.outputDirectory + "/VSM.html");
        }

        auto fsm = createShaderModule(desc.fragmentShaderPath);
        if(desc.exportASTAsDot){
            fsm->exportAstDot(desc.outputDirectory + "-FSM.dot");
        }
        if(desc.exportSymbolTableAsHtml){
            fsm->exportSymbolTableHtml(desc.outputDirectory + "-FSM.html");
        }

        auto program = createShaderProgram();
        program->addShaderModule(vsm);
        program->addShaderModule(fsm);
        program->link();

        CppDescriptor cppDesc;
        cppDesc.outputFile = desc.outputDirectory;
        program->exportCpp(cppDesc);

        delete program;
    }

    void generateExecutable(const GeneratorDesc& desc){
        compileProgram(desc);

    }
}