#include <stdexcept>
#include "Environment.hpp"

namespace SrslRuntime{

    Environment::Environment() {

    }

    void Environment::execute(const InterfaceDataDesc &inputData, InterfaceDataDesc &outputData) {
        if (inputData.size % inputData.stride != 0){
            throw std::runtime_error("Provided input data is not aligned properly");
        }
        auto elementCount = inputData.size / inputData.stride;
        auto outputBuffer = new char[inputData.stride * elementCount]; // allocate memory for the output buffer

        auto bytePtr = reinterpret_cast<char*>(inputData.data);

        // first, run vertex Shader
        for (size_t i = 0; i < inputData.size; i += inputData.stride){
            auto inputElement = bytePtr + i;
            auto outputElement = outputBuffer + i;
            auto result = main1(reinterpret_cast<void*>(inputElement));
            memcpy(outputElement, result, inputData.stride);
        }

        delete[] outputBuffer;

    }
}