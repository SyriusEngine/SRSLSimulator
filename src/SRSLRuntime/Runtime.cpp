#include "Runtime.hpp"

namespace SrslRuntime{

    Runtime::Runtime(const std::string &dataFile):
    m_ColorBuffer(s_ImageWidth, s_ImageHeight, 4),
    m_DepthBuffer(s_ImageWidth, s_ImageHeight, 1){
        m_Environment = new Environment(dataFile);

        // initialize the depth buffer
        m_DepthBuffer.clear(std::numeric_limits<float>::infinity());
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
            auto minX = std::min(std::min(v0["SRV_POSITION"].x, v1["SRV_POSITION"].x), v2["SRV_POSITION"].x);
            auto minY = std::min(std::min(v0["SRV_POSITION"].y, v1["SRV_POSITION"].y), v2["SRV_POSITION"].y);
            auto maxX = std::max(std::max(v0["SRV_POSITION"].x, v1["SRV_POSITION"].x), v2["SRV_POSITION"].x);
            auto maxY = std::max(std::max(v0["SRV_POSITION"].y, v1["SRV_POSITION"].y), v2["SRV_POSITION"].y);

            for (uint32_t x = minX; x <= maxX; x++){
                for (uint32_t y = minY; y <= maxY; y++){
                    auto barryC = calculateBarryCentricCoords(v0, v1, v2, x, y);

                    // if the point is inside the triangle, then calculate the depth and color
                    if (barryC.a >= 0.0f && barryC.b >= 0.0f && barryC.c >= 0.0f){
                        auto interpolated = interpolateAttributes(v0, v1, v2, barryC);
                        auto depth = barryC.a * v0["SRV_POSITION"].z + barryC.b * v1["SRV_POSITION"].z + barryC.c * v2["SRV_POSITION"].z;

                        // execute fragment shader if the pixel is visible
                        if (depth < m_DepthBuffer(x, y, 1)){
                            m_DepthBuffer(x, y, 1) = depth;
                            Fragment fragment;
                            main__Fragment(interpolated, fragment, m_Environment);
                            m_ColorBuffer(x, y, 1) = fragment["SRV_TARGET_0"].x;
                            m_ColorBuffer(x, y, 2) = fragment["SRV_TARGET_0"].y;
                            m_ColorBuffer(x, y, 3) = fragment["SRV_TARGET_0"].z;
                            printf("Pixel (%d, %d) is visible\n", x, y);
                        }
                    }
                }
            }
        }
        m_ColorBuffer.save("Output.png");
    }

    BarryCentricCoordinates
    Runtime::calculateBarryCentricCoords(Vertex &v0, Vertex &v1, Vertex &v2, uint32_t x, uint32_t y) {
        auto v0x = v0["SRV_POSITION"].x;
        auto v0y = v0["SRV_POSITION"].y;
        auto v1x = v1["SRV_POSITION"].x;
        auto v1y = v1["SRV_POSITION"].y;
        auto v2x = v2["SRV_POSITION"].x;
        auto v2y = v2["SRV_POSITION"].y;

        BarryCentricCoordinates bcc;
        bcc.a = (v1y - v2y) * (x - v2x) + (v2x - v1x) * (y - v2y);
        bcc.b = (v2y - v0y) * (x - v2x) + (v0x - v2x) * (y - v2y);
        bcc.c = 1.0f - bcc.a - bcc.b;

        return bcc;
    }

    Vertex Runtime::interpolateAttributes(Vertex &v0, Vertex &v1, Vertex &v2, BarryCentricCoordinates &bcc) {
        Vertex result;
        for (auto [key, value]: v0){
            result[key] = bcc.a * v0[key] + bcc.b * v1[key] + bcc.c * v2[key];
        }
        return result;
    }
}
