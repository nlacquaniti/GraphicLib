#include "OpenGLImpl/Utils/ShaderImplUtils.h"

#include "FmtFormat.h"
#include "GraphicLib/Utilities/ShaderUtils.h"
#include "InternalLogger.h"
#include <glad/glad.h>
#include <fstream>
#include <string>


namespace GraphicLib::OpenGLImpl {
std::string ShaderImplUtils::LoadFromFile(const char* shaderPath) {
    std::ifstream file{shaderPath};
    if (!file.is_open()) {
        const std::string& errorText = fmt::format("shaderPath {} doesn't exist", shaderPath);
        LOG_INTERNAL_ERROR(errorText.c_str());
        return {};
    }

    std::string fileContent{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    file.close();
    return fileContent;
}

bool ShaderImplUtils::ConvertShaderType(EShaderType type, unsigned int& outType) {
    switch (type) {
        case GraphicLib::EShaderType::VERTEX:
            outType = GL_VERTEX_SHADER;
            return true;
        case GraphicLib::EShaderType::FRAGMENT:
            outType = GL_FRAGMENT_SHADER;
            return true;
        case GraphicLib::EShaderType::COMPUTE:
            outType = GL_COMPUTE_SHADER;
            return true;
        case GraphicLib::EShaderType::GEOMETRY:
            outType = GL_GEOMETRY_SHADER;
            return true;
        case GraphicLib::EShaderType::TESS_CONTROL:
            outType = GL_TESS_CONTROL_SHADER;
            return true;
        case GraphicLib::EShaderType::TESS_EVALUATION:
            outType = GL_TESS_EVALUATION_SHADER;
            return true;
        case GraphicLib::EShaderType::NONE:
            break;
    }

    const std::string& errorText = fmt::format("ShaderType {}", ShaderUtils::ShaderTypeToString(type));
    LOG_INTERNAL_ERROR(errorText.c_str());
    return false;
}
} // namespace GraphicLib::OpenGLImpl
