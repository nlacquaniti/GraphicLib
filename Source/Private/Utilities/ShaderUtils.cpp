#include "GraphicLib/Utilities/ShaderUtils.h"

#include "InternalLogger.h"
#include <fmt/format.h>
#include <fstream>
#include <string>

namespace GraphicLib {
const char* ShaderUtils::ShaderTypeToString(EShaderType shaderType) {
    switch (shaderType) {
        case EShaderType::NONE:
            return "NONE";
        case EShaderType::VERTEX:
            return "VERTEX";
        case EShaderType::FRAGMENT:
            return "FRAGMENT";
        case EShaderType::COMPUTE:
            return "COMPUTE";
        case EShaderType::GEOMETRY:
            return "GEOMETRY";
        case EShaderType::TESS_CONTROL:
            return "TESS CONTROL";
        case EShaderType::TESS_EVALUATION:
            return "TESS EVALUATION";
    }
    return "ERROR";
}
} // namespace GraphicLib
