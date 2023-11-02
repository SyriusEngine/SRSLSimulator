#include <iostream>
#include "include/SRSLGenerator/SRSLGenerator.hpp"
#include "include/SLDF_File_ver2.hpp"

struct Vertex{
    float x, y, z;
    float r, g, b;
    float nx, ny, nz;
    float u, v;
};

int main(int argc, char** argv) {
    try {
        sldf::SLDF_File file;

        std::vector<sldf::VertexAttribute> vertexAttributes = {
                {"position", 3, sizeof(float)},
                {"color", 3, sizeof(float)},
                {"normal", 3, sizeof(float)},
                {"texCoord", 2, sizeof(float)}
        };
        std::vector<Vertex> triangle = {
                {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f},
                {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.f, 0.f, 0.f, 1.f, 1.f, 0.f},
                {0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.f, 0.f, 0.f, 1.f, 0.5f, 1.f}
        };
        std::vector<uint32_t> indices = {
                0, 1, 2
        };

        file.setVertexData("vsIn", triangle.data(), triangle.size() * sizeof(Vertex), vertexAttributes.data(), vertexAttributes.size());
        file.setIndexData("indices", indices.data(), 3, sizeof(uint32_t));

        file.save("test.sldf");

        sldf::SLDF_File file2("test.sldf");
        std::cout << "File loaded" << std::endl;




//        SrslGenerator::GeneratorDesc desc;
//        desc.vertexShaderPath = "./SRSLShaders/Basic-vs.srsl";
//        desc.fragmentShaderPath = "./SRSLShaders/Basic-fs.srsl";
//        SrslGenerator::generateExecutable(desc);

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}