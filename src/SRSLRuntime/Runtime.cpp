#include "Runtime.hpp"

namespace SrslRuntime{

    Runtime::Runtime(const std::string &dataFile) {
        m_Environment = new Environment(dataFile);
    }

    Runtime::~Runtime() {
        delete m_Environment;
    }

    void Runtime::execute() {
        printf("===================Vertex Shader===================\n");
        auto vertexOutput = vertexShaderStage();
        printf("===================Fragment Shader===================\n");
    }

    std::unique_ptr<char[]> Runtime::vertexShaderStage(){
        auto& vertexDataFrame = m_Environment->m_SLDFFile.getFrameByType(SLDF_INPUT);
        auto& pVertexData = vertexDataFrame->getData();

        // dataSize divided by the size of the input vertex struct results in the number of vertices
        // each vertex has an output result of size sizeof(Vertex_OUTPUT)
        // therefore, we can preallocate the output buffer
        auto pVertexOut = std::make_unique<char[]>(sizeof(Vertex_OUTPUT) * (vertexDataFrame->getDataSize() / sizeof(Vertex_INPUT)));
        uint64_t j = 0;
        for (uint64_t i = 0; i < vertexDataFrame->getDataSize(); i += sizeof(Vertex_INPUT)){
            auto vertexIn = reinterpret_cast<Vertex_INPUT*>(pVertexData.get() + i);
            auto vertexOut = reinterpret_cast<void*>(pVertexOut.get() + j);

            main__Vertex(vertexIn, vertexOut, m_Environment);

            j += sizeof(Vertex_OUTPUT);
        }
        return std::move(pVertexOut);
    }

}
