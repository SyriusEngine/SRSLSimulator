cmake_minimum_required(VERSION 3.24)
project(SRSLSimulator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SyriusShadingLanguage)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SyriusShadingLanguage)

add_compile_definitions(SRSL_GRAPHICS_API_EXPORT_DLL)

include_directories(./Dependencies/)
include_directories(./SyriusShadingLanguage/include/)

link_directories(./cmake-build-debug/)
link_directories(./cmake-build-debug/SyriusShadingLanguage/)

set(SRSL_GRAPHICS_API_SRC
    src/GraphicsAPI/Pipeline.cpp
    src/GraphicsAPI/ContextImpl.cpp
    src/GraphicsAPI/SrslAPI.cpp src/GraphicsAPI/VertexLayout.cpp src/GraphicsAPI/Include.cpp src/GraphicsAPI/Context.cpp src/GraphicsAPI/VertexBufferImpl.cpp src/GraphicsAPI/VertexBufferImpl.hpp)

add_library(SrslAPI SHARED ${SRSL_GRAPHICS_API_SRC})
target_link_libraries(SrslAPI -lSrslCompiler)

add_executable(SrslSimulator main.cpp)
target_link_libraries(SrslSimulator -lSrslAPI)




###########################################################################

# TEMPORARY EXECUTABLE FOR TESTING

###########################################################################
