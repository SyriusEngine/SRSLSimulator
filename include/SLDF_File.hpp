#pragma once

#include <string>
#include <fstream>
#include <memory>

typedef enum SLDF_DATA_TYPE: uint8_t{
    SLDF_INPUT = 0x01,
    SLDF_OUTPUT = 0x02,
    SLDF_CONSTANT_BUFFER = 0x03,
    SLDF_TEXTURE = 0x04,
} SLDF_DATA_TYPE;

namespace sldf{

    class DataFrame{
    public:
        explicit DataFrame(std::ifstream& file){
            // read the header
            char header[24];
            file.read(header, 24);
            m_Version = std::string(header, 6);
            m_Type = static_cast<SLDF_DATA_TYPE>(header[6]);
            // read the Semantic size from the header
            uint64_t nameSize;
            memcpy(&nameSize, header + 7, 8);
            memcpy(&m_DataSize, header + 15, 8);

            // read the semantic name from the file
            char* name = new char[nameSize];
            file.read(name, nameSize);
            m_Name = std::string(name, nameSize);
            delete[] name;

            // read the data from the file
            m_Data = std::make_unique<char[]>(m_DataSize);
            file.read(m_Data.get(), m_DataSize);

            // read the next frame
            if (file.peek() != EOF){
                m_NextFrame = std::make_unique<DataFrame>(file);
            }
        }

        explicit DataFrame(const std::string& name, SLDF_DATA_TYPE type):
        m_Name(name),
        m_Type(type),
        m_Version("SLDF10"),
        m_Data(nullptr),
        m_DataSize(0),
        m_NextFrame(nullptr){

        }

        void setData(void* data, uint64_t dataSize){
            m_Data = std::make_unique<char[]>(dataSize);
            memcpy(m_Data.get(), data, dataSize);
            m_DataSize = dataSize;
        }

        [[nodiscard]] const std::string& getName() const{
            return m_Name;
        }

        [[nodiscard]] SLDF_DATA_TYPE getType() const{
            return m_Type;
        }

        [[nodiscard]] const std::unique_ptr<char[]>& getData() const{
            return m_Data;
        }

        [[nodiscard]] uint64_t getDataSize() const{
            return m_DataSize;
        }

        [[nodiscard]] DataFrame* addFrame(const std::string& name, SLDF_DATA_TYPE type){
            if (m_NextFrame == nullptr){
                m_NextFrame = std::make_unique<DataFrame>(name, type);
                return m_NextFrame.get();
            }
            else{
                return m_NextFrame->addFrame(name, type);
            }
        }

        void save(std::ofstream& file){
            // write the header
            char header[24];
            memcpy(header, m_Version.c_str(), 6);
            header[6] = m_Type;
            // write the Semantic size to the header
            uint64_t nameSize = m_Name.size();
            memcpy(header + 7, &nameSize, 8);
            memcpy(header + 15, &m_DataSize, 8);
            // zero out the flag byte for now
            header[23] = 0;
            file.write(header, 24);

            // write the semantic name to the file
            file.write(m_Name.c_str(), nameSize);
            file.write(m_Data.get(), m_DataSize);

            if (m_NextFrame != nullptr){
                m_NextFrame->save(file);
            }
        }

        std::unique_ptr<DataFrame>& getFrame(const std::string& name){
            if (m_NextFrame->m_Name == name){
                return m_NextFrame;
            }
            else{
                return m_NextFrame->getFrame(name);
            }
        }

    private:
        std::string m_Version;
        std::string m_Name;
        SLDF_DATA_TYPE m_Type;
        std::unique_ptr<char[]> m_Data;
        uint64_t m_DataSize;
        std::unique_ptr<DataFrame> m_NextFrame;
    };

    class SLDF_File{
    public:
        SLDF_File()= default;

        explicit SLDF_File(const std::string& dataFile){
            std::ifstream file(dataFile, std::ios::binary);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open file: " + dataFile);
            }
            m_FirstFrame = std::make_unique<DataFrame>(file);
        }

        ~SLDF_File(){

        }

        DataFrame* addFrame(const std::string& name, SLDF_DATA_TYPE type){
            if (m_FirstFrame == nullptr){
                m_FirstFrame = std::make_unique<DataFrame>(name, type);
                return m_FirstFrame.get();
            }
            else{
                return m_FirstFrame->addFrame(name, type);
            }
        }

        void save(const std::string& fileName){
            std::ofstream file(fileName, std::ios::binary);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open file: " + fileName);
            }
            if (m_FirstFrame != nullptr){
                m_FirstFrame->save(file);
            }
        }

        std::unique_ptr<DataFrame>& getFrame(const std::string& name){
            if (m_FirstFrame->getName() == name){
                return m_FirstFrame;
            }
            else{
                return m_FirstFrame->getFrame(name);
            }
        }

    private:
        std::unique_ptr<DataFrame> m_FirstFrame;
    };

}