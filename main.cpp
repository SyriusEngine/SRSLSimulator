#include <iostream>
#include "include/SRSLGenerator/SRSLGenerator.hpp"


int main(int argc, char** argv) {
    try {
        SrslGenerator::GeneratorDesc desc;
        desc.outputDirectory = "SRSLShaders/Basic-vs.srsl";
        desc.vertexShaderPath = "SRSLShaders/Basic-fs.srsl";
        desc.fragmentShaderPath = "src/SRSLRuntime/Shader/Basic";
        SrslGenerator::generateExecutable(desc);

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}