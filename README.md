# SRSLSimulator
## Introduction
The SRSLSimulator is a tool that simulates the GPU graphics pipeline on a high level. It works in combination with the 
SRSL Compiler (https://github.com/SyriusEngine/SyriusShadingLanguage). The SRSL Compiler is a compiler that compiles the 
domain specific SRSL language to GLSL or HLSL. The SRSLSimulator builds upon this compiler to also allow exporting SRSL 
to C++. The shadercode (in C++) can then be loaded into the SRSLSimulator to execute the shaders on the CPU. The 
Simulator extends this function by introducing a debugging tool which uses GDB.

## Motivation
The SRSLSimulator was created to allow for a more efficient shader development process. Since writing bugs is a common
thing when creating software projects, having a debugger makes finding these bugs a lot easier. Debugging of shaders
is not an easy task since the GPU behaves in a vastly different way than the CPU. The SRSLSimulator tries to solve this
by executing the shaders on the CPU making use of well established debugging tools like GDB. This tool makesit possible
to quickly spot bugs in the shader code and fix them.

## Features
Since this project is done individually, not every feature from a current day graphics pipeline is supported. The
following list shows the features that are currently supported by the SRSLSimulator:
- Creating vertex and index buffers
- uploading textures
- rendering to render targets and saving them to disk
- executing and debugging shaders
  - Vertex shaders
  - Fragment shaders
- uploading and updating constant buffers

## Supported platforms
The SRSLSimulator relies heavily on the WIN32 API and GDB. Therefore it is only supported on Windows.
## Installation
### Requirements
- A C++ 17 compiler, such as MSVC2019 or GCC 9.3.0
- CMake 3.16 or higher
- GDB 8.3 or higher

### Dependencies
All these dependencies are already included in the repository as submodules. Therefore they do not need to be installed
manually.
- SRSL Compiler (https://github.com/SyriusEngine/SyriusShadingLanguage)
- SyriusCore (https://github.com/SyriusEngine/SyriusCore)
- Nlohmann JSON (https://github.com/nlohmann/json)

### Building
The SRSLSimulator uses CMake as its build system. Therefore it is possible to build the project using the CMake GUI or
the command line. The following steps show how to build the project using the command line:
1. Clone the repository
2. Initialize the submodules
3. Create a build directory
4. Run CMake
5. Build the project

```bash
git clone
git submodule update --init --recursive
mkdir build
cd build
cmake ..
cmake --build .
```

