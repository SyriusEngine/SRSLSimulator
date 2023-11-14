#include "../../include/GraphicsAPI/VertexLayout.hpp"

namespace SrslAPI{

    VertexLayout::VertexLayout():
    m_Stride(0){

    }

    void VertexLayout::pushAttribute(const std::string &name, SRSL_SCALAR_TYPE type) {
        VertexAttribute attribute;
        attribute.name = name;
        attribute.typeSize = getTypeSize(getScalarType(type));
        attribute.componentCount = getComponentCount(type);
        attribute.size = attribute.typeSize * attribute.componentCount;

        m_Attributes.push_back(attribute);
        m_Stride += getScalarSize(type);

    }
}
