#include "../../include/GraphicsAPI/Include.hpp"

namespace SrslAPI{

    uint8_t getTypeSize(SRSL_TYPE type){
        switch (type) {
            case SRSL_TYPE_NONE:  return 0;
            case SRSL_VOID:       return 0;
            case SRSL_UINT8:      return 1;
            case SRSL_INT8:       return 1;
            case SRSL_UINT16:     return 2;
            case SRSL_INT16:      return 2;
            case SRSL_UINT32:     return 4;
            case SRSL_INT32:      return 4;
            case SRSL_UINT64:     return 8;
            case SRSL_INT64:      return 8;
            case SRSL_FLOAT16:    return 2;
            case SRSL_FLOAT32:    return 4;
            case SRSL_FLOAT64:    return 8;
            default: {
                throw std::runtime_error("Unknown type");
            }
        }
    }

    uint8_t getComponentCount(SRSL_SCALAR_TYPE scalarType){
        uint8_t trunc = scalarType << 4;
        uint8_t shifted = (trunc >> 4);
        shifted++;
        return shifted;
    }

    uint8_t getScalarSize(SRSL_SCALAR_TYPE scalarType){
        uint8_t trunc = scalarType << 4;
        uint8_t shifted = (trunc >> 4);
        shifted++;
        return getTypeSize(static_cast<SRSL_TYPE>(static_cast<SRSL_TYPE>((scalarType >> 4) << 4))) * shifted;
    }

    SRSL_TYPE getScalarType(SRSL_SCALAR_TYPE scalarType){
        return static_cast<SRSL_TYPE>((scalarType >> 4) << 4);
    }

}
