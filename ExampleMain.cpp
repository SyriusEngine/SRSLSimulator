#include "src/Examples/Shared/Display.hpp"
#include "src/Examples/Interpolation.hpp"
#include "src/Examples/Texture.hpp"
#include "src/Examples/MultipleTextures.hpp"
#include "src/Examples/ConstantBuffer.hpp"
#include "src/Examples/MVP.hpp"

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
    runTest<Simulator::TextureLayer>(configName);
    runTest<Simulator::MultipleTexturesLayer>(configName);
    runTest<Simulator::ConstantBufferLayer>(configName);
    runTest<Simulator::MVPLayer>(configName);
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
            } else if (arg == "Texture"){
                runTest<Simulator::TextureLayer>(configName);
            } else if (arg == "MultipleTextures"){
                runTest<Simulator::MultipleTexturesLayer>(configName);
            } else if (arg == "ConstantBuffer"){
                runTest<Simulator::ConstantBufferLayer>(configName);
            } else if (arg == "MVP"){
                runTest<Simulator::MVPLayer>(configName);
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