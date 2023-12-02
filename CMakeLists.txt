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

set(SRSL_API_DEPENDECIES_SRC
    src/GraphicsAPI/Dependencies/stb_image_write.cpp
    src/GraphicsAPI/Dependencies/stb_image.cpp
)

set(SRSL_GRAPHICS_API_SRC
    ${SRSL_API_DEPENDECIES_SRC}
    src/GraphicsAPI/Impl/Pipeline.cpp
    src/GraphicsAPI/Impl/ContextImpl.cpp
    src/GraphicsAPI/SrslAPI.cpp
    src/GraphicsAPI/VertexLayout.cpp
    src/GraphicsAPI/Include.cpp
    src/GraphicsAPI/Context.cpp
    src/GraphicsAPI/Impl/VertexBufferImpl.cpp
    src/GraphicsAPI/Impl/IndexBufferImpl.cpp
    src/GraphicsAPI/Shader.cpp
    src/GraphicsAPI/Impl/ShaderImpl.cpp
    src/GraphicsAPI/FrameBuffer.cpp
    src/GraphicsAPI/ColorAttachment.cpp
    src/GraphicsAPI/Impl/FrameBufferImpl.cpp
    src/GraphicsAPI/ConstantBuffer.cpp
    src/GraphicsAPI/Impl/ConstantBufferImpl.cpp
    src/GraphicsAPI/Profiler.cpp
    src/GraphicsAPI/Texture2D.cpp
    src/GraphicsAPI/Impl/Texture2DImpl.cpp
    src/GraphicsAPI/Impl/Texture2DImpl.hpp
)

add_library(SrslAPI SHARED ${SRSL_GRAPHICS_API_SRC})
target_link_libraries(SrslAPI -lSrslCompiler)


include_directories(./include/)
include_directories(./Dependencies/SyriusCore/include/)

file(GLOB SYRIUSCORE_DLL "./Dependencies/SyriusCore/bin/*.dll")
file(COPY ${SYRIUSCORE_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/SyriusShadingLanguage)

set(SIMULATOR_SRC
    src/Simulator/Simulator.cpp
)

add_executable(SrslSimulator main.cpp ${SIMULATOR_SRC})
target_link_libraries(SrslSimulator -lSrslAPI -lSyriusCore)

