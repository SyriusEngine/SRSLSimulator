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
        vertexShaderStage();
        printf("===================Primitive Assembly===================\n");
        primitiveAssemblyStage();
        printf("===================Rasterizer===================\n");
        rasterizerStage();
    }

    void Runtime::vertexShaderStage(){
        auto& vertexDataFrame = m_Environment->m_SLDFFile.getVertexData();
        auto& vertexData = vertexDataFrame->getData();
        auto vertexDataSize = vertexDataFrame->getDataSize();
        auto attributes = vertexDataFrame->getAttributes();

        uint64_t vertexStride = 0;
        for (auto& attribute: attributes){
            vertexStride += attribute.componentCount * attribute.componentSize;
        }

        auto vertexCount = vertexDataSize / vertexStride;
        m_Vertices.resize(vertexCount);
        uint32_t vertexID = 0;
        for (uint64_t i = 0; i < vertexDataSize; i += vertexStride){
            // the vertex shader input data is the only one whose type is unknown, so cast the data
            // directly to the input type that the shader expects
            auto inMem = std::make_unique<char[]>(sizeof(Vertex_INPUT));
            // zero out memory for top level struct
            for (uint64_t k = 0; k < sizeof(VertexInput); k++){
                inMem[k] = 0;
            }
            // copy the data from the SLDF file into the input vertex,
            memcpy(inMem.get() + sizeof(VertexInput), vertexData.get() + i, vertexStride);
            // cast the input vertex to the correct type
            auto vertexIn = reinterpret_cast<Vertex_INPUT*>(inMem.get());
            vertexIn->SRV_VERTEX_ID = vertexID;

            main__Vertex(vertexIn, m_Vertices[vertexID], m_Environment);
            vertexID++;
        }
    }

    void Runtime::primitiveAssemblyStage() {
        auto& indexDataFrame = m_Environment->m_SLDFFile.getIndexData();
        auto& indexData = indexDataFrame->getData();
        auto indexSize = indexDataFrame->getIndexSize();
        auto indexCount = indexDataFrame->getIndexCount();

        if (indexCount % 3 != 0){
            throw std::runtime_error("Supplied index data is not a triangle list");
        }

        m_Indices.resize(indexCount);

        switch (indexSize){
            case sizeof(uint8_t):{
                for (uint64_t i = 0; i < indexCount; i++){
                    m_Indices.push_back(indexData[i]);
                }
                break;
            }
            case sizeof(uint16_t):{
                for (uint64_t i = 0; i < indexCount; i++){
                    m_Indices.push_back(reinterpret_cast<uint16_t*>(indexData.get())[i]);
                }
                break;
            }
            case sizeof(uint32_t):{
                for (uint64_t i = 0; i < indexCount; i++){
                    m_Indices.push_back(reinterpret_cast<uint32_t*>(indexData.get())[i]);
                }
                break;
            }
            default:{
                throw std::runtime_error("Invalid index size: " + std::to_string(indexSize) + " bytes");
            }
        }
    }

    void Runtime::rasterizerStage() {
        for (uint64_t i = 0; i < m_Indices.size(); i += 3){
            auto& v0 = m_Vertices[m_Indices[i]];
            auto& v1 = m_Vertices[m_Indices[i + 1]];
            auto& v2 = m_Vertices[m_Indices[i + 2]];

            // rasterize
        }

    }

}
