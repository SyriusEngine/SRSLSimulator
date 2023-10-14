cmake_minimum_required(VERSION 3.24)
project(SRSLSimulator)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SyriusShadingLanguage)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SyriusShadingLanguage)

include_directories(include/)
include_directories(./SyriusShadingLanguage/include/)

link_directories(./cmake-build-debug/)
link_directories(./cmake-build-debug/SyriusShadingLanguage/)

#set(SRSL_RUNTIME_SRC )
#
#add_library(SrslRuntime SHARED ${SRSL_RUNTIME_SRC})

add_executable(SRSLSimulator main.cpp)
target_link_libraries(SRSLSimulator -lSrslCompiler)
