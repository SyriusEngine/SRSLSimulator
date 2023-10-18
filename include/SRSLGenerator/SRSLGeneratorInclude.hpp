#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <SrslCompiler.hpp>
#include <memory>

// identify operating system and toolchain
#if defined(WIN64) || defined(_WIN64) || defined(WIN32)
#if defined(SRSL_EXPORT_DLL)
#define SRSL_GEN_API __declspec(dllexport)
#else
#define SRSL_GEN_API __declspec(dllimport)
#endif
#else
#define SRSL_GEN_API

#endif

namespace SrslGenerator{

}