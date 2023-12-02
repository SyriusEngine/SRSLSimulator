#include "../../include/GraphicsAPI/Texture2D.hpp"

namespace SrslAPI{

    Texture2D::Texture2D(const Texture2DDesc &desc):
    m_Width(desc.width),
    m_Height(desc.height),
    m_ChannelCount(desc.channels){

    }

    Texture2D::Texture2D(const ImageDesc &desc):
    m_Width(0),
    m_Height(0),
    m_ChannelCount(0){

    }

    Texture2D::~Texture2D() {

    }
}
