cmake_minimum_required(VERSION 3.24)
project(SRSLSimulator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SyriusShadingLanguage)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SyriusShadingLanguage)

include_directories(Dependencies/)
include_directories(./SyriusShadingLanguage/include/)

link_directories(./cmake-build-debug/)
link_directories(./cmake-build-debug/SyriusShadingLanguage/)

set(SRSL_RUNTIME_SRC
        src/SRSLRuntime/Environment.cpp)

add_executable(SrslRuntime ${SRSL_RUNTIME_SRC} src/SRSLRuntime/RuntimeMain.cpp)

add_executable(SRSLSimulator main.cpp)
target_link_libraries(SRSLSimulator -lSrslCompiler)
