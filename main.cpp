#include <iostream>
#include "src/Simulator/Simulator.hpp"

struct Vertex{
    float x, y, z;
    float r, g, b;
    float nx, ny, nz;
    float u, v;
};

int main(int argc, char** argv) {
    try {
        Simulator::Simulator simulator;
        simulator.run();



    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}