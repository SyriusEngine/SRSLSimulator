#pragma once

#include "SimulatorInclude.hpp"
#include "SimulatorStore.hpp"

namespace Simulator{

    struct TextureBindable{
        uint32 slot;
        UP<Texture2D> texture;
    };

    class Renderer{
    public:
        explicit Renderer(SimulatorStore& store);

        ~Renderer() = default;

        void draw() const;

        void savePipelineConfig(const std::string& path);

        void loadPipelineConfig(const std::string& path);

        void loadShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

        void loadMesh();

        void loadTexture(const std::string& filePath, uint32 slot = 0, bool flipOnLoad = true);

    public:
        UP<VertexLayout> vertexLayout;
        UP<FrameBuffer> frameBuffer;

    private:
        SimulatorStore& m_Store;

        uint32 m_Width;
        uint32 m_Height;

        UP<Context> m_Context;

        UP<Shader> m_Shader;
        UP<VertexBuffer> m_VertexBuffer;
        UP<IndexBuffer> m_IndexBuffer;

        std::vector<TextureBindable> m_Textures;
    };

}