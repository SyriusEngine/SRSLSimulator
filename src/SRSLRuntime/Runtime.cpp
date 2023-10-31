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

    std::vector<Vertex_OUTPUT> Runtime::vertexShaderStage(){
        auto& vertexDataFrame = m_Environment->m_SLDFFile.getFrameByType(SLDF_INPUT);
        auto& pVertexData = vertexDataFrame->getData();
        /* Vertex_INPUT is defined by the shader interface, which ALWAYS inherits from VertexInput
         * To get the size of an individual input vertex, we subtract the size of the VertexInput struct from the size of the Vertex_INPUT struct
         * That way, only the attributes defined by the shader interface are counted, which is also the data stored in the SLDF file
         *
         * We make the assumption that the data stored in always has at least 1 attribute.
         */
        assert(sizeof(Vertex_INPUT) > sizeof(VertexInput));
        uint32_t incomingVertexSize = sizeof(Vertex_INPUT) - sizeof(VertexInput);
        uint64_t vertexCount = vertexDataFrame->getDataSize() / incomingVertexSize;

        std::vector<Vertex_OUTPUT> vertexOutput(vertexCount); // allocate space for the output vertices
        uint64_t vertexID = 0;
        for (uint64_t i = 0; i < vertexDataFrame->getDataSize(); i += sizeof(Vertex_INPUT)){
            // allocate memory for the input vertex
            auto inMem = std::make_unique<char[]>(sizeof(Vertex_INPUT));
            // zero out memory for top level struct
            for (uint64_t k = 0; k < sizeof(VertexInput); k++){
                inMem[k] = 0;
            }
            // copy the data from the SLDF file into the input vertex
            memcpy(inMem.get() + sizeof(VertexInput), pVertexData.get() + i, incomingVertexSize);
            // cast the input vertex to the correct type
            auto vertexIn = reinterpret_cast<Vertex_INPUT*>(inMem.get());
            vertexIn->SRV_VERTEX_ID = vertexID;

            main__Vertex(vertexIn, &vertexOutput[vertexID], m_Environment);

            vertexID++;
        }
        return vertexOutput;
    }

}
