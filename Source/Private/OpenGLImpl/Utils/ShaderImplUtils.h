#pragma once

#include "GraphicLib\Shader.h"
#include <string>

namespace GraphicLib {
namespace OpenGLImpl {
class ShaderImplUtils final {
public:
    static std::string LoadFromFile(const char* shaderPath);
    static bool ConvertShaderType(EShaderType type, unsigned int& outType);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
