#pragma once

#include "GraphicLib\Shader.h"
#include <string>

namespace GraphicLib::OpenGLImpl {
class ShaderImplUtils {
public:
    static std::string LoadFromFile(const char* shaderPath);
    static bool ConvertShaderType(EShaderType type, unsigned int& outType);
};
} // namespace GraphicLib::OpenGLImpl
