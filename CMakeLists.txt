cmake_minimum_required(VERSION 3.24)
project(SRSLSimulator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SyriusShadingLanguage)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SyriusShadingLanguage)

include_directories(./Dependencies/)
include_directories(./SyriusShadingLanguage/include/)

link_directories(./cmake-build-debug/)
link_directories(./cmake-build-debug/SyriusShadingLanguage/)

set(SRSL_GENERATOR_SRC
    src/SRSLGenerator/SRSLGenerator.cpp )

add_library(SrslGenerator SHARED ${SRSL_GENERATOR_SRC})
target_link_libraries(SrslGenerator -lSrslCompiler)

set(SRSL_SIMULATOR_SRC)

add_executable(SrslSimulator ${SRSL_SIMULATOR_SRC} main.cpp)
target_link_libraries(SrslSimulator -lSrslGenerator)
