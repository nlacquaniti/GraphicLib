#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Shader.h"

namespace GraphicLib {
class DLL_API ShaderUtils {
public:
    static const char* ShaderTypeToString(EShaderType shaderType);
};
} // namespace GraphicLib
