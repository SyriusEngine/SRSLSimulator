#include <iostream>
#include "include/SRSLGenerator/SRSLGenerator.hpp"
#include "include/SLDF_File.hpp"

struct Vertex{
    float x, y, z;
};

int main(int argc, char** argv) {
    try {
        sldf::SLDF_File f;

        auto vertexDataFrame = f.addFrame("vertexData", SLDF_VERTEX_DATA);
        std::vector<Vertex> inputData = {
                {0.5f, 0.0f, 0.0f},
                {0.0f, 0.5f, 0.0f},
                {-0.5f, 0.0f, 0.0f}
        };
        vertexDataFrame->setData(inputData.data(), inputData.size() * sizeof(Vertex));

        auto indexDataFrame = f.addFrame("indexData", SLDF_INDEX_DATA);
        std::vector<uint32_t> indexData = {
                0, 1, 2
        };
        indexDataFrame->setData(indexData.data(), indexData.size() * sizeof(uint32_t));


        f.save("test.sldf");


        SrslGenerator::GeneratorDesc desc;
        desc.vertexShaderPath = "./SRSLShaders/Basic-vs.srsl";
        desc.fragmentShaderPath = "./SRSLShaders/Basic-fs.srsl";
        SrslGenerator::generateExecutable(desc);

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}