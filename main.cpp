#include <iostream>
#include "include/SRSLGenerator/SRSLGenerator.hpp"


int main(int argc, char** argv) {
    try {
        SrslGenerator::GeneratorDesc desc;
        desc.vertexShaderPath = "./SRSLShaders/Basic-vs.srsl";
        desc.fragmentShaderPath = "./SRSLShaders/Basic-fs.srsl";
        SrslGenerator::generateExecutable(desc);

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}