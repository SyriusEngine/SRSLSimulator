#include <iostream>
#include <chrono>
#include <glm/glm.hpp>
#include "include/GraphicsAPI/SrslAPI.hpp"

struct Vertex{
    float x, y, z;
    float r, g, b;
    float nx, ny, nz;
    float u, v;
};

time_t getTime(){
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

int main(int argc, char** argv) {
    try {
        using namespace SrslAPI;

        auto ctx = createContext();

        auto vl = ctx->createVertexLayout();
        vl->pushAttribute("Position", SRSL_FLOAT32_3);
        vl->pushAttribute("Color", SRSL_FLOAT32_3);
        vl->pushAttribute("Normal", SRSL_FLOAT32_3);
        vl->pushAttribute("TexCoords", SRSL_FLOAT32_2);

        std::vector<Vertex> rectangle = {
                {-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.f, 0.f, 0.f, 0.f, 0.f},
                {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, -1.f, 0.f, 0.f, 1.f, 0.f},
                {0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, -1.f, 0.f, 0.f, 1.f, 1.f},
                {-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, -1.f, 0.f, 0.f, 0.f, 1.f}
        };
        auto vertexBuffer = ctx->createVertexBuffer(vl, rectangle.data(), rectangle.size() * sizeof(Vertex));

        std::vector<uint32_t> indices = {
                0, 1, 2,
                2, 3, 0
        };
        auto indexBuffer = ctx->createIndexBuffer(indices.data(), indices.size());

        auto preShader = getTime();
        auto shader = ctx->createShader("./SRSLShaders/Basic-vs.srsl", "./SRSLShaders/Basic-fs.srsl");
        auto postShader = getTime();
        std::cout << "Shader compilation time: " << postShader - preShader << std::endl;

        ColorAttachmentDesc desc;
        desc.width = 1280;
        desc.height = 720;
        desc.channelCount = 4;
        desc.clearColor[0] = 0.2f;
        desc.clearColor[1] = 0.3f;
        desc.clearColor[2] = 0.8f;
        desc.clearColor[3] = 1.0f;

        FrameBufferLayout fbLayout;
        fbLayout.setViewport(1280, 720, 0, 0);
        fbLayout.addColorAttachment(desc);

        auto fb = ctx->createFrameBuffer(fbLayout);
        fb->getColorAttachment(0)->clear();

        glm::mat4 modelData(1.0f);
        ConstantBufferDesc cbd;
        cbd.name = "ModelData";
        cbd.size = sizeof(glm::mat4);
        cbd.data = &modelData;
        auto cb = ctx->createConstantBuffer(cbd);





        // ======================= DRAW =======================
        auto preFrame = getTime();
        fb->bind();
        vertexBuffer->bind();
        indexBuffer->bind();
        shader->bind();
        cb->bind();
        ctx->draw();
        auto postFrame = getTime();

        std::cout << "Frame time: " << postFrame - preFrame << std::endl;

        fb->getColorAttachment(0)->save("test.png");



    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}