#include <iostream>
#include "Environment.hpp"

struct Vertex{
    float x, y, z;
    float u, v;
};

int main(int argc, char** argv) {
    try {
        std::vector<Vertex> inputData = {
            { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f },
            { 1.0f, 1.0f, 0.0f, 1.0f, 1.0f },
            { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f }
        };

        SrslRuntime::InterfaceDataDesc inputDesc;
        inputDesc.data = inputData.data();
        inputDesc.size = inputData.size() * sizeof(Vertex);
        inputDesc.stride = sizeof(Vertex);

        SrslRuntime::Environment env;
        env.execute(inputDesc, inputDesc);



    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
