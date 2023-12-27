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
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <path/to/config.ini>" << std::endl;
            return 1;
        }
        Simulator::Simulator simulator(argv[1]);
        simulator.run();

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}