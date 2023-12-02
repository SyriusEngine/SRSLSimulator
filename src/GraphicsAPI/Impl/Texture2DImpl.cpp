#include "Texture2DImpl.hpp"
#include "../Dependencies/stb_image.hpp"
#include "Pipeline.hpp"

namespace SrslAPI{

    Texture2DImpl::Texture2DImpl(const Texture2DDesc &desc, Pipeline *pipeline) :
    Texture2D(desc),
    m_Pipeline(pipeline),
    m_Data(){
        m_Data.width = desc.width;
        m_Data.height = desc.height;
        m_Data.channels = desc.channels;
        m_Data.data.resize(desc.dataSize);
        memcpy(m_Data.data.data(), desc.data, desc.dataSize);
    }

    Texture2DImpl::Texture2DImpl(const ImageDesc &desc, Pipeline *pipeline) :
    Texture2D(desc),
    m_Pipeline(pipeline),
    m_Data(){
        stbi_set_flip_vertically_on_load(desc.flipOnLoad);
        auto ptr = stbi_load(desc.path.c_str(), (int*)&m_Data.width, (int*)&m_Data.height, (int*)&m_Data.channels, 4);
        if (ptr){
            m_Data.data.resize(m_Data.width * m_Data.height * m_Data.channels);
            memcpy(m_Data.data.data(), ptr, m_Data.data.size());
            m_Width = m_Data.width;
            m_Height = m_Data.height;
            m_ChannelCount = m_Data.channels;
        }

    }

    Texture2DImpl::~Texture2DImpl() {

    }

    void Texture2DImpl::bind(uint32_t slot) {
        m_Pipeline->bindTexture(slot, reinterpret_cast<char*>(&m_Data));
    }
}