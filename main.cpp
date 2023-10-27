#include <iostream>
#include "include/SRSLGenerator/SRSLGenerator.hpp"
#include "include/SLDF_File.hpp"

struct Vertex{
    float x, y, z;
};

struct ProjectionData{
    float data[4][4];
};

int main(int argc, char** argv) {
    try {
        SrslSimulator::SLDF_File f;
        auto inputFrame = f.addFrame("input", SLDF_INPUT);

        std::vector<Vertex> inputData = {
                {1.0f, 1.5f, 2.3f},
                {2.0f, 1.8f, 5.0f},
                {3.0f, 2.0f, 1.0f}
        };
        inputFrame->setData(inputData.data(), inputData.size() * sizeof(Vertex));

        ProjectionData pD;
        pD.data[0][0] = 1.0f;
        pD.data[0][1] = 0.0f;
        pD.data[0][2] = 0.0f;
        pD.data[0][3] = 0.0f;
        pD.data[1][0] = 0.0f;
        pD.data[1][1] = 1.0f;
        pD.data[1][2] = 0.0f;
        pD.data[1][3] = 0.0f;
        pD.data[2][0] = 0.0f;
        pD.data[2][1] = 0.0f;
        pD.data[2][2] = 1.0f;
        pD.data[2][3] = 0.0f;
        pD.data[3][0] = 0.0f;
        pD.data[3][1] = 0.0f;
        pD.data[3][2] = 0.0f;
        pD.data[3][3] = 1.0f;
        auto pFrame = f.addFrame("Projection", SLDF_CONSTANT_BUFFER);
        pFrame->setData(&pD, sizeof(ProjectionData));


        f.save("test.sldf");


//        SrslGenerator::GeneratorDesc desc;
//        desc.vertexShaderPath = "./SRSLShaders/Basic-vs.srsl";
//        desc.fragmentShaderPath = "./SRSLShaders/Basic-fs.srsl";
//        SrslGenerator::generateExecutable(desc);

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}