#include "src/Examples/Shared/Display.hpp"

int main(int argc, char** argv){
    try{
        Simulator::Display display("config.ini");
        display.run();

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception" << std::endl;
    }
    return 0;
}