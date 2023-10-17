#include <iostream>
#include "SyriusShadingLanguage/include/SrslCompiler.hpp"

void compile(const std::string& vertex, const std::string& fragment, const std::string& output){
    auto vsm = Srsl::createShaderModule(vertex);
    vsm->exportAstDot("VSM.dot");
    vsm->exportSymbolTableHtml("VSM.html");

    auto fsm = Srsl::createShaderModule(fragment);
    fsm->exportAstDot("FSM.dot");
    fsm->exportSymbolTableHtml("FSM.html");

    auto program = Srsl::createShaderProgram();
    program->addShaderModule(vsm);
    program->addShaderModule(fsm);
    program->link();

    Srsl::CppDescriptor desc;
    desc.outputFile = output;
    program->exportCpp(desc);
}

int main(int argc, char** argv) {
    try {
        compile("SRSLShaders/Basic-vs.srsl", "SRSLShaders/Basic-fs.srsl", "src/SRSLRuntime/Shader/Basic");

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}