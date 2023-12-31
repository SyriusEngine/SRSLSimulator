#include "Renderer.hpp"
#include "Panels/ShaderPanel.hpp"
#include "Panels/PipelinePanel.hpp"

namespace Simulator{

    Renderer::Renderer(SimulatorStore &store):
    m_Store(store),
    shader(nullptr),
    m_VertexBuffer(nullptr),
    m_IndexBuffer(nullptr),
    m_RenderThread(){
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
        m_RenderThread.addTask([this](){
            frameBuffer->getColorAttachment(0)->clear();

            if (shader != nullptr && m_VertexBuffer != nullptr && m_IndexBuffer != nullptr){
                frameBuffer->bind();

                shader->bind();
                m_VertexBuffer->bind();
                m_IndexBuffer->bind();
                for (const auto& texture: m_Textures){
                    texture.texture->bind(texture.slot);
                }

                m_Context->draw();
            }
        });
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

        // background color
        float* clearColor = frameBuffer->getColorAttachment(0)->getClearColor();
        config["Pipeline"]["BackgroundColor"]["r"] = clearColor[0];
        config["Pipeline"]["BackgroundColor"]["g"] = clearColor[1];
        config["Pipeline"]["BackgroundColor"]["b"] = clearColor[2];
        config["Pipeline"]["BackgroundColor"]["a"] = clearColor[3];

        // shaders
        config["Pipeline"]["Shaders"]["VertexShaderPath"] = m_Store.vertexShaderPath;
        config["Pipeline"]["Shaders"]["FragmentShaderPath"] = m_Store.fragmentShaderPath;

        // vertex buffer
        for (const auto& vertex: m_Store.vertices){
            nlohmann::json vertexJson;
            for (uint32 attrIndex = 0; attrIndex < attributes.size(); attrIndex++){
                nlohmann::json attributeJson;
                for (uint32 componentIndex = 0; componentIndex < attributes[attrIndex].componentCount; componentIndex++){
                    attributeJson.push_back(vertex[attrIndex][componentIndex]);
                }
                vertexJson[attributes[attrIndex].name] = attributeJson;
            }
            config["Pipeline"]["VertexBuffer"].push_back(vertexJson);
        }

        // index buffer
        for (const auto& index: m_Store.indices){
            config["Pipeline"]["IndexBuffer"].push_back(index);
        }

        // textures
        for (const auto& texture: m_Store.textures){
            config["Pipeline"]["Textures"].push_back({
                {"Slot", texture.slot},
                {"FilePath", texture.path},
                {"FlipOnLoad", texture.flipOnLoad},
            });
        }

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

        // background color
        float r = config["Pipeline"]["BackgroundColor"]["r"].get<float>();
        float g = config["Pipeline"]["BackgroundColor"]["g"].get<float>();
        float b = config["Pipeline"]["BackgroundColor"]["b"].get<float>();
        float a = config["Pipeline"]["BackgroundColor"]["a"].get<float>();
        frameBuffer->getColorAttachment(0)->setClearColor(r, g, b, a);

        // shaders
        m_Store.vertexShaderPath = config["Pipeline"]["Shaders"]["VertexShaderPath"].get<std::string>();
        m_Store.fragmentShaderPath = config["Pipeline"]["Shaders"]["FragmentShaderPath"].get<std::string>();
        loadShaders(m_Store.vertexShaderPath, m_Store.fragmentShaderPath);

        // vertex buffer
        const auto& vertices = config["Pipeline"]["VertexBuffer"];
        const auto& loadedAttributes = vertexLayout->getAttributes();
        for (const auto& vertex: vertices){
            UIVertex uiVertex;
            for (const auto& attr: loadedAttributes){
                const auto& attribute = vertex[attr.name];
                uiVertex.emplace_back(attr.componentCount);
                for (uint32 componentIndex = 0; componentIndex < attr.componentCount; componentIndex++){
                    uiVertex.back()[componentIndex] = attribute[componentIndex];
                }
            }
            m_Store.vertices.push_back(uiVertex);
        }

        // index buffer
        const auto& indices = config["Pipeline"]["IndexBuffer"];
        for (const auto& index: indices){
            m_Store.indices.push_back(index);
        }
        loadMesh();

        // textures
        const auto& textures = config["Pipeline"]["Textures"];
        for (const auto& texture: textures){
            uint32 slot = texture["Slot"].get<uint32>();
            std::string texPath = texture["FilePath"].get<std::string>();
            bool flipOnLoad = texture["FlipOnLoad"].get<bool>();
            loadTexture(texPath, slot, flipOnLoad);
        }

    }

    void Renderer::loadShaders(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
        auto pVertexShaderPanel = dynamic_cast<ShaderPanel*>(m_Store.vertexShaderPanel.get());
        auto pFragmentShaderPanel = dynamic_cast<ShaderPanel*>(m_Store.fragmentShaderPanel.get());

        pVertexShaderPanel->loadShader(vertexShaderPath);
        pFragmentShaderPanel->loadShader(fragmentShaderPath);

        if (vertexShaderPath.empty() || fragmentShaderPath.empty()){
            return;
        }
        shader = m_Context->createShader(vertexShaderPath, fragmentShaderPath);
        auto& debugInfo = shader->getDebugInfo();
        m_Store.compiledVertexShaderPath = debugInfo.vertexShaderCppSource;
        m_Store.compiledFragmentShaderPath = debugInfo.fragmentShaderCppSource;

        auto loadLineInfo = [](ShaderLineInfo& lineInfo, const std::string& lineInfoPath){
            std::ifstream file(lineInfoPath);
            std::string line;
            while (std::getline(file, line)){
                auto splitted = splitString(line, ':');
                uint32 srslLine = std::stoi(splitted[0]);

                std::stringstream ss(splitted[1]);
                std::string nr;
                std::vector<uint32> cppLines;
                while (std::getline(ss, nr, ' ')){
                    if (!nr.empty()){
                        cppLines.emplace_back(std::stoi(nr));
                    }
                }
                lineInfo.insert({srslLine, cppLines});
            }
        };
        loadLineInfo(m_Store.vertexShaderLineInfo, debugInfo.vertexShaderLineInfo);
        loadLineInfo(m_Store.fragmentShaderLineInfo, debugInfo.fragmentShaderLineInfo);
    }

    void Renderer::loadMesh() {
        std::vector<float> vertices;
        for (const auto& vertex : m_Store.vertices){
            for (const auto& attribute : vertex){
                for (const auto& component : attribute){
                    vertices.emplace_back(component);
                }
            }
        }
        m_VertexBuffer = m_Context->createVertexBuffer(vertexLayout, vertices.data(), vertices.size() * sizeof(UIVertex));
        m_IndexBuffer = m_Context->createIndexBuffer(m_Store.indices.data(), m_Store.indices.size());
    }

    void Renderer::loadTexture(const std::string &filePath, uint32 slot, bool flipOnLoad) {
        ImageDesc loader;
        loader.path = filePath;
        loader.flipOnLoad = flipOnLoad;

        TextureBindable bindable;
        bindable.slot = slot;
        bindable.texture = m_Context->createTexture2D(loader);

        m_Textures.push_back(std::move(bindable));

        TextureStorage storage;
        storage.flipOnLoad = flipOnLoad;
        storage.path = filePath;
        storage.slot = slot;

        m_Store.textures.push_back(std::move(storage));
    }

}