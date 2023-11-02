#pragma once

#include <string>
#include <fstream>
#include <memory>

#define VERSION_SIZE 8
#define FRAME_TYPE_SIZE 1
#define NAME_SIZE 4
#define DATA_HEADER_SIZE 4
#define DATA_SIZE 4


typedef enum SLDF_FRAME_TYPE: uint8_t{
    SLDF_VERTEX_DATA = 0x01,
    SLDF_INDEX_DATA = 0x02,
    SLDF_CONSTANT_BUFFER = 0x03,
    SLDF_TEXTURE = 0x04,
} SLDF_FRAME_TYPE;

namespace sldf{

    struct VertexAttribute{
        std::string name;
        uint8_t componentCount;
        uint8_t componentSize;
    };

    class Frame{
    public:
        Frame(SLDF_FRAME_TYPE type, const std::string& name):
                m_Data(nullptr),
                m_DataSize(0),
                m_Layout(nullptr),
                m_LayoutSize(0),
                m_Type(type),
                m_Name(name){

        }

        Frame(SLDF_FRAME_TYPE type, std::ifstream& file):
                m_Data(nullptr),
                m_DataSize(0),
                m_Layout(nullptr),
                m_LayoutSize(0),
                m_Type(type){
            char header[15];
            file.read(header, 15);
            uint32_t nameSize;
            memcpy(&nameSize, header, NAME_SIZE); // read name size
            memcpy(&m_LayoutSize, header + NAME_SIZE, DATA_HEADER_SIZE); // read layout size
            memcpy(&m_DataSize, header + NAME_SIZE + DATA_HEADER_SIZE, DATA_SIZE); // read data size

            // read the name
            char* name = new char[nameSize];
            file.read(name, nameSize);
            m_Name = std::string(name, nameSize);
        }

        virtual ~Frame() = default;

        virtual void save(std::ofstream& file){
            char header[16];
            memcpy(header, &m_Type, FRAME_TYPE_SIZE);
            uint32_t nameSize = m_Name.size();
            memcpy(header + FRAME_TYPE_SIZE, &nameSize, NAME_SIZE);
            memcpy(header + FRAME_TYPE_SIZE + NAME_SIZE, &m_LayoutSize, DATA_HEADER_SIZE);
            memcpy(header + FRAME_TYPE_SIZE + NAME_SIZE + DATA_HEADER_SIZE, &m_DataSize, DATA_SIZE);
            file.write(header, 16);
            file.write(m_Name.c_str(), nameSize);
        }

        [[nodiscard]] const std::unique_ptr<char[]>& getData() const{
            return m_Data;
        }

        [[nodiscard]] uint32_t getDataSize() const{
            return m_DataSize;
        }

    protected:
        std::string m_Name;
        SLDF_FRAME_TYPE m_Type;
        std::unique_ptr<char[]> m_Data;
        uint32_t m_DataSize;
        std::unique_ptr<char[]> m_Layout;
        uint32_t m_LayoutSize;
    };

    class VertexDataFrame: public Frame{
    public:
        explicit VertexDataFrame(std::ifstream& file):
                Frame(SLDF_VERTEX_DATA, file){
            // read the attributes
            auto buffer = std::make_unique<char[]>(m_LayoutSize);
            file.read(buffer.get(), m_LayoutSize);

            uint32_t offset = 0;
            while (offset < m_LayoutSize){
                uint8_t componentCount = buffer[offset];
                uint8_t componentSize = buffer[offset + 1];
                uint32_t nameSize;
                memcpy(&nameSize, buffer.get() + offset + 2, NAME_SIZE);
                std::string name(buffer.get() + offset + 2 + NAME_SIZE, nameSize);
                m_Attributes.push_back({name, componentCount, componentSize});
                offset += 2 + NAME_SIZE + nameSize;
            }

            // read the data
            m_Data = std::make_unique<char[]>(m_DataSize);
            file.read(m_Data.get(), m_DataSize);

        }

        VertexDataFrame(const std::string& name, const void* data, uint64_t dataSize, const VertexAttribute* attributes, uint8_t attributeCount):
                Frame(SLDF_VERTEX_DATA, name){
            // copy the data
            m_Data = std::make_unique<char[]>(dataSize);
            memcpy(m_Data.get(), data, dataSize);
            m_DataSize = dataSize;

            // copy the layout
            for (uint8_t i = 0; i < attributeCount; i++){
                m_Attributes.push_back(attributes[i]);
                m_LayoutSize += 2 + NAME_SIZE + attributes[i].name.size();
            }
        }

        void save(std::ofstream& file) override{
            Frame::save(file);
            // write the attributes
            for (auto& attribute: m_Attributes){
                file.write(reinterpret_cast<char*>(&attribute.componentCount), 1);
                file.write(reinterpret_cast<char*>(&attribute.componentSize), 1);

                uint32_t nameSize = attribute.name.size();
                file.write(reinterpret_cast<char*>(&nameSize), NAME_SIZE);
                file.write(attribute.name.c_str(), nameSize);
            }

            // write the data
            file.write(m_Data.get(), m_DataSize);
        }

        [[nodiscard]] const std::vector<VertexAttribute>& getAttributes() const{
            return m_Attributes;
        }

    private:
        std::vector<VertexAttribute> m_Attributes;
    };

    class IndexDataFrame: public Frame{
    public:
        explicit IndexDataFrame(std::ifstream& file):
                Frame(SLDF_INDEX_DATA, file),
                m_IndexSize(0){
            // index buffer has a header of 8 bytes
            char buffer[8];
            file.read(buffer, 8);
            memcpy(&m_IndexSize, buffer, 1);
            memcpy(&m_IndexCount, buffer + 1, 4);

            // read the data
            m_Data = std::make_unique<char[]>(m_DataSize);
            file.read(m_Data.get(), m_DataSize);
        }

        IndexDataFrame(const std::string& name, const void* data, uint32_t indexCount, uint8_t indexSize):
                Frame(SLDF_INDEX_DATA, name),
                m_IndexSize(indexSize),
                m_IndexCount(indexCount){
            m_DataSize = indexCount * indexSize;
            m_Data = std::make_unique<char[]>(m_DataSize);
            memcpy(m_Data.get(), data, m_DataSize);
        }

        void save(std::ofstream& file) override {
            Frame::save(file);
            char header[8];
            memcpy(header, &m_IndexSize, 1);
            memcpy(header + 1, &m_IndexCount, 4);
            file.write(header, 8);
            file.write(m_Data.get(), m_DataSize); // write data
        }

        [[nodiscard]] uint8_t getIndexSize() const{
            return m_IndexSize;
        }

        [[nodiscard]] uint32_t getIndexCount() const{
            return m_IndexCount;
        }

    private:
        uint8_t m_IndexSize;
        uint32_t m_IndexCount;
    };

    class SLDF_File{
    public:
        SLDF_File():
                m_Version("SLDF0101"){

        }

        explicit SLDF_File(const std::string& fileName){
            std::ifstream file(fileName, std::ios::binary);
            if (!file.is_open()){
                throw std::runtime_error("Failed to open file");
            }
            char header[VERSION_SIZE];
            file.read(header, VERSION_SIZE);
            m_Version = std::string(header, VERSION_SIZE);
            if (m_Version != "SLDF0101"){
                throw std::runtime_error("Invalid file version");
            }
            // read the first frame
            while(file.peek() != EOF){
                // read the frame type, before creating the actual frame
                char frameType;
                file.read(&frameType, FRAME_TYPE_SIZE);
                auto type = static_cast<SLDF_FRAME_TYPE>(frameType);
                switch(type){
                    case SLDF_VERTEX_DATA: {
                        m_VertexData = std::make_unique<VertexDataFrame>(file);
                        break;
                    }
                    case SLDF_INDEX_DATA: {
                        m_IndexData = std::make_unique<IndexDataFrame>(file);
                        break;
                    }
                    default: {
                        throw std::runtime_error("Invalid frame type");
                    }
                }
            }

        }

        void save(const std::string& fileName){
            std::ofstream file(fileName, std::ios::binary);
            if (!file.is_open()){
                throw std::runtime_error("Failed to open file");
            }
            // write the version
            file.write(m_Version.c_str(), VERSION_SIZE);
            // write the frames
            m_VertexData->save(file);
            m_IndexData->save(file);
        }

        void setVertexData(const std::string& name, const void* data, uint64_t dataSize, const VertexAttribute* attributes, uint8_t attributeCount){
            m_VertexData = std::make_unique<VertexDataFrame>(name, data, dataSize, attributes, attributeCount);
        }

        void setIndexData(const std::string& name, const void* data, uint32_t indexCount, uint8_t indexSize){
            m_IndexData = std::make_unique<IndexDataFrame>(name, data, indexCount, indexSize);
        }

        std::unique_ptr<VertexDataFrame>& getVertexData(){
            return m_VertexData;
        }

        std::unique_ptr<IndexDataFrame>& getIndexData(){
            return m_IndexData;
        }

    private:
        std::string m_Version;
        std::unique_ptr<VertexDataFrame> m_VertexData;
        std::unique_ptr<IndexDataFrame> m_IndexData;

    };





}