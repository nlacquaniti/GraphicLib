#pragma once

#include "GraphicLib/Shader.h"
#include <string>

namespace GraphicLib::Internal {
std::string LoadFromFile(const char* shaderPath);
bool ConvertShaderType(EShaderType type, unsigned int& outType);
} // namespace GraphicLib::Internal
