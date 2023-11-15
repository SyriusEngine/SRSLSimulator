#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <stdexcept>
#include <limits>

#if defined(WIN64) || defined(_WIN64) || defined(WIN32)
#if defined(SRSL_GRAPHICS_API_EXPORT_DLL)
#define SRSL_GRAPHICS_API __declspec(dllexport)
#else
#define SRSL_GRAPHICS_API __declspec(dllimport)
#endif
#else
#define SRSL_GRAPHICS_API
#endif

// basic types
typedef enum SRSL_TYPE: uint8_t {
    SRSL_TYPE_NONE    = 0x00,
    SRSL_VOID         = 0x10,
    SRSL_UINT8        = 0x20,
    SRSL_INT8         = 0x30,
    SRSL_UINT16       = 0x40,
    SRSL_INT16        = 0x50,
    SRSL_UINT32       = 0x60,
    SRSL_INT32        = 0x70,
    SRSL_UINT64       = 0x80,
    SRSL_INT64        = 0x90,
    SRSL_FLOAT16      = 0xA0,
    SRSL_FLOAT32      = 0xB0,
    SRSL_FLOAT64      = 0xC0,
} SRSL_DATA_TYPE;

// scalar types
// upper 4 bits are the data type
// lower 4 bits are the component count (NOTE: 0 represents 1 component, F represents 16 components)
typedef enum SRSL_SCALAR_TYPE: uint8_t {
    SRSL_UINT8_1      = 0x20,
    SRSL_UINT8_2      = 0x21,
    SRSL_UINT8_3      = 0x22,
    SRSL_UINT8_4      = 0x23,
    SRSL_UINT8_3X3    = 0x2B,
    SRSL_UINT8_4X4    = 0x2F,

    SRSL_INT8_1       = 0x30,
    SRSL_INT8_2       = 0x31,
    SRSL_INT8_3       = 0x32,
    SRSL_INT8_4       = 0x33,
    SRSL_INT8_3X3     = 0x3B,
    SRSL_INT8_4X4     = 0x3F,

    SRSL_UINT16_1     = 0x40,
    SRSL_UINT16_2     = 0x41,
    SRSL_UINT16_3     = 0x42,
    SRSL_UINT16_4     = 0x43,
    SRSL_UINT16_3X3   = 0x4B,
    SRSL_UINT16_4X4   = 0x4F,

    SRSL_INT16_1      = 0x50,
    SRSL_INT16_2      = 0x51,
    SRSL_INT16_3      = 0x52,
    SRSL_INT16_4      = 0x53,
    SRSL_INT16_3X3    = 0x5B,
    SRSL_INT16_4X4    = 0x5F,

    SRSL_UINT32_1     = 0x60,
    SRSL_UINT32_2     = 0x61,
    SRSL_UINT32_3     = 0x62,
    SRSL_UINT32_4     = 0x63,
    SRSL_UINT32_3X3   = 0x6B,
    SRSL_UINT32_4X4   = 0x6F,

    SRSL_INT32_1      = 0x70,
    SRSL_INT32_2      = 0x71,
    SRSL_INT32_3      = 0x72,
    SRSL_INT32_4      = 0x73,
    SRSL_INT32_3X3    = 0x7B,
    SRSL_INT32_4X4    = 0x7F,

    SRSL_UINT64_1     = 0x80,
    SRSL_UINT64_2     = 0x81,
    SRSL_UINT64_3     = 0x82,
    SRSL_UINT64_4     = 0x83,
    SRSL_UINT64_3X3   = 0x8B,
    SRSL_UINT64_4X4   = 0x8F,

    SRSL_INT64_1      = 0x90,
    SRSL_INT64_2      = 0x91,
    SRSL_INT64_3      = 0x92,
    SRSL_INT64_4      = 0x93,
    SRSL_INT64_3X3    = 0x9B,
    SRSL_INT64_4X4    = 0x9F,

    SRSL_FLOAT16_1    = 0xA0,
    SRSL_FLOAT16_2    = 0xA1,
    SRSL_FLOAT16_3    = 0xA2,
    SRSL_FLOAT16_4    = 0xA3,
    SRSL_FLOAT16_3X3  = 0xAB,
    SRSL_FLOAT16_4X4  = 0xAF,

    SRSL_FLOAT32_1    = 0xB0,
    SRSL_FLOAT32_2    = 0xB1,
    SRSL_FLOAT32_3    = 0xB2,
    SRSL_FLOAT32_4    = 0xB3,
    SRSL_FLOAT32_3X3  = 0xBB,
    SRSL_FLOAT32_4X4  = 0xBF,

    SRSL_FLOAT64_1    = 0xC0,
    SRSL_FLOAT64_2    = 0xC1,
    SRSL_FLOAT64_3    = 0xC2,
    SRSL_FLOAT64_4    = 0xC3,
    SRSL_FLOAT64_3X3  = 0xCB,
    SRSL_FLOAT64_4X4  = 0xCF,
} SRSL_SCALAR_TYPE;

namespace SrslAPI{

    template<typename T>
    using UP = std::unique_ptr<T>;

    // RCP = Reference Counting Pointer => because i'm a lazy and do not want to type std::shared_pointer every time
    template<typename T>
    using RCP = std::shared_ptr<T>;

    template<typename T, typename... Args>
    inline UP<T> createUP(Args&&... args){
        return std::make_unique<T>(args...);
    }

    template<typename T, typename... Args>
    inline RCP<T> createRCP(Args&&... args){
        return std::make_shared<T>(args...);
    }

    SRSL_GRAPHICS_API uint8_t getTypeSize(SRSL_TYPE type);

    SRSL_GRAPHICS_API uint8_t getComponentCount(SRSL_SCALAR_TYPE scalarType);

    SRSL_GRAPHICS_API uint8_t getScalarSize(SRSL_SCALAR_TYPE scalarType);

    SRSL_GRAPHICS_API SRSL_TYPE getScalarType(SRSL_SCALAR_TYPE scalarType);


}