#include <iostream>
#include "include/SRSLGenerator/SRSLGenerator.hpp"
#include "include/SLDF_File.hpp"

struct Vertex{
    float x, y, z;
};

int main(int argc, char** argv) {
    try {
        sldf::SLDF_File f;
        auto inputFrame = f.addFrame("input", SLDF_INPUT);

        std::vector<Vertex> inputData = {
                {0.5f, 0.0f, 0.0f},
                {0.0f, 0.5f, 0.0f},
                {-0.5f, 0.0f, 0.0f}
        };
        inputFrame->setData(inputData.data(), inputData.size() * sizeof(Vertex));

        f.save("test.sldf");


        SrslGenerator::GeneratorDesc desc;
        desc.vertexShaderPath = "./SRSLShaders/Basic-vs.srsl";
        desc.fragmentShaderPath = "./SRSLShaders/Basic-fs.srsl";
        SrslGenerator::generateExecutable(desc);

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}