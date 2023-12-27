#include "Renderer.hpp"

namespace Simulator{

    Renderer::Renderer(SimulatorStore &store):
    m_Store(store) {
        m_Context = createContext();

        m_Width = m_Store.config["Simulation"]["SimulationWidth"].getOrDefault<uint32>(DRAW_WIDTH);
        m_Height = m_Store.config["Simulation"]["SimulationHeight"].getOrDefault<uint32>(DRAW_HEIGHT);

        ColorAttachmentDesc caDesc;
        caDesc.width = m_Width;
        caDesc.height = m_Height;
        caDesc.channelCount = 4;
        caDesc.clearColor[0] = 0.8f;
        caDesc.clearColor[1] = 0.7f;
        caDesc.clearColor[2] = 0.3f;
        caDesc.clearColor[3] = 1.0f;

        FrameBufferLayout fbLayout;
        fbLayout.setViewport(m_Width, m_Height, 0, 0);
        fbLayout.addColorAttachment(caDesc);

        frameBuffer = m_Context->createFrameBuffer(fbLayout);
        frameBuffer->getColorAttachment(0)->clear();

        vertexLayout = m_Context->createVertexLayout();
    }

    void Renderer::draw() {
        frameBuffer->getColorAttachment(0)->clear();
    }

    void Renderer::savePipelineConfig(const std::string &path) {
        nlohmann::json config;
        // vertex Layout
        const auto& attributes = vertexLayout->getAttributes();
        for(const auto& attribute: attributes){
            config["Pipeline"]["VertexLayout"]["Attributes"].push_back({
                {"Name", attribute.name},
                {"Count", attribute.componentCount},
            });
        }
        config["Pipeline"]["VertexLayout"]["Stride"] = vertexLayout->getStride();

        // save to file
        std::ofstream file(path);
        file << config.dump(4);
        file.close();
    }

    void Renderer::loadPipelineConfig(const std::string &path) {
        std::ifstream file(path);
        nlohmann::json config;
        file >> config;
        file.close();

        // vertex Layout
        vertexLayout = m_Context->createVertexLayout();
        const auto& attributes = config["Pipeline"]["VertexLayout"]["Attributes"];
        for(const auto& attribute: attributes){
            vertexLayout->pushAttribute(attribute["Name"].get<std::string>(), cCountToType(attribute["Count"].get<uint32>()));
        }

    }

}