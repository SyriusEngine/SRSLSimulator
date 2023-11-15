#include <iostream>
#include "include/GraphicsAPI/SrslAPI.hpp"

struct Vertex{
    float x, y, z;
    float r, g, b;
    float nx, ny, nz;
    float u, v;
};

int main(int argc, char** argv) {
    try {
        using namespace SrslAPI;

        auto ctx = createContext();

        auto vl = ctx->createVertexLayout();
        vl->pushAttribute("Position", SRSL_FLOAT32_3);
        vl->pushAttribute("Color", SRSL_FLOAT32_3);
        vl->pushAttribute("Normal", SRSL_FLOAT32_3);
        vl->pushAttribute("TexCoords", SRSL_FLOAT32_2);

        std::vector<Vertex> triangle = {
                {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.f, 0.f, 0.f, 1.f, 0.f},
                {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.f, 0.f, 0.f, 1.f, 1.f},
                {0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.f, 0.f, 0.f, 1.f, 0.5f}
        };
        auto vertexBuffer = ctx->createVertexBuffer(vl, triangle.data(), triangle.size() * sizeof(Vertex));

        std::vector<uint32_t> indices = {
                0, 1, 2
        };
        auto indexBuffer = ctx->createIndexBuffer(indices.data(), indices.size());

        auto shader = ctx->createShader("./SRSLShaders/Basic-vs.srsl", "./SRSLShaders/Basic-fs.srsl");


        vertexBuffer->bind();
        indexBuffer->bind();
        shader->bind();
        ctx->draw();


    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}