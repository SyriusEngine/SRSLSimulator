#include "src/Examples/Shared/Display.hpp"
#include "src/Examples/Interpolation.hpp"

template<typename T>
void runTest(const std::string& configName){
    try{
        Simulator::Display display(configName);
        display.addLayer<T>();
        display.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception" << std::endl;
    }
}

void runAll(const std::string& configName){
    runTest<Simulator::InterpolationLayer>(configName);
}

int main(int argc, char** argv){
    try{
        if (argc < 2){
            std::cout << "Usage: " << argv[0] << " <config file>" << std::endl;
            return 0;
        }
        const std::string configName = argv[1];
        for (uint32 i = 2; i < argc; ++i){
            std::string arg = argv[i];
            if (arg == "Interpolation"){
                runTest<Simulator::InterpolationLayer>(configName);
            } else if (arg == "All"){
                runAll(configName);
            }
            else{
                std::cerr << "Unknown argument: " << arg << std::endl;
            }
        }

    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cout << "Unknown exception" << std::endl;
    }
    return 0;
}