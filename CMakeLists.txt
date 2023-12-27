cmake_minimum_required(VERSION 3.24)
project(SRSLSimulator)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./Dependencies/SyriusCore)
add_subdirectory(./Dependencies/SyriusShadingLanguage)

include_directories(./Dependencies/)

set(SRSL_DEPENDECIES_DLL
    ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/SyriusCore/libSyriusCore.dll
    ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/SyriusShadingLanguage/libSrslCompiler.dll
    ${CMAKE_CURRENT_BINARY_DIR}/Dependencies/SyriusShadingLanguage/libantlr4-runtime.dll
    )

add_custom_target(CopyDLL ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRSL_DEPENDECIES_DLL} ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${SRSL_DEPENDECIES_DLL}
    COMMENT "Copying DLLs to build tree")


add_compile_definitions(SRSL_GRAPHICS_API_EXPORT_DLL)

link_directories(./cmake-build-debug/)

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

add_dependencies(SrslAPI CopyDLL)


include_directories(./include/)
include_directories(./Dependencies/SyriusCore/include/)
include_directories(./Dependencies/glm/)
include_directories(./Dependencies/glm/glm/)
include_directories(./Dependencies/EasyIni/include/)
include_directories(./Dependencies/json/include/)

set(SIMULATOR_SRC
    src/Simulator/Simulator.cpp
    src/Simulator/SimulatorStore.cpp src/Simulator/SimulatorStore.hpp src/Simulator/Panels/Panel.cpp src/Simulator/Panels/Panel.hpp src/Simulator/Panels/NavBar.cpp src/Simulator/Panels/NavBar.hpp)

add_executable(SrslSimulator main.cpp ${SIMULATOR_SRC})
target_link_libraries(SrslSimulator -lSrslAPI -lSyriusCore)

