#include "OpenGLImpl/ShaderImpl.h"

#include "GraphicLib/Utilities/ShaderUtils.h"
#include "InternalLogger.h"
#include "Utils/ShaderImplUtils.h"
#include <glad/glad.h>
#include <array>
#include <format>
#include <string>


namespace GraphicLib::OpenGLImpl {
void ShaderImpl::Initialise(unsigned int& id, const std::span<const ShaderData>& data) const {
    id = glCreateProgram();

    std::array<unsigned int, Shader::MAX_DATA_COUNT> shaderIDs;
    for (std::size_t i{}; i < data.size(); ++i) {
        if (!_createShader(data[i], shaderIDs.at(i))) {
            return;
        }
        glAttachShader(id, shaderIDs.at(i));
    }

    glLinkProgram(id);
    int successfullyCompiled{};
    glGetProgramiv(id, GL_LINK_STATUS, &successfullyCompiled);
    if (successfullyCompiled == 0) {
        std::array<char, 1024> logText;
        glGetShaderInfoLog(id, static_cast<int>(logText.size()), nullptr, logText.data());
        LOG_INTERNAL_ERROR(logText.data());
    }

    for (std::size_t i{}; i < data.size(); ++i) {
        glDeleteShader(shaderIDs.at(i));
    }
}

void ShaderImpl::Bind(unsigned int id) const {
    glUseProgram(id);
}

void ShaderImpl::Unbind(unsigned int /*unused*/) const {
    glUseProgram(0);
}

void ShaderImpl::SetUniformBoolValue(unsigned int id, const char* name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name), static_cast<int>(value));
}

void ShaderImpl::SetUniformIntValue(unsigned int id, const char* name, int value) const {
    glUniform1i(glGetUniformLocation(id, name), value);
}

void ShaderImpl::SetUniformFloatValue(unsigned int id, const char* name, float value) const {
    glUniform1f(glGetUniformLocation(id, name), value);
}

void ShaderImpl::SetUniformMat4Value(unsigned int id, const char* name, const float* value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, value);
}

void ShaderImpl::Delete(unsigned int& id) const {
    glDeleteProgram(id);
    id = 0;
}

bool ShaderImpl::_createShader(const ShaderData& shaderData, unsigned int& id) const {
    unsigned int shaderType{};
    if (!ShaderImplUtils::ConvertShaderType(shaderData.Type, shaderType)) {
        const std::string logText = std::format("Can't EShaderType {} to OpenGL shader type", ShaderUtils::ShaderTypeToString(shaderData.Type));
        LOG_INTERNAL_ERROR(logText.c_str());
        return false;
    }

    const std::string& shaderContent = ShaderImplUtils::LoadFromFile(shaderData.FilePath.data());
    if (shaderContent.empty()) {
        const std::string logText = std::format("Can't open shader at path {}", shaderData.FilePath.data());
        LOG_INTERNAL_ERROR(logText.c_str());
        return false;
    }

    id = glCreateShader(shaderType);
    const char* shaderContentCStr = shaderContent.c_str();
    glShaderSource(id, 1, &shaderContentCStr, nullptr);
    glCompileShader(id);

    int successfullyCompiled{};
    glGetShaderiv(id, GL_COMPILE_STATUS, &successfullyCompiled);
    if (successfullyCompiled == 0) {
        std::array<char, 1024> logText{};
        glGetShaderInfoLog(id, static_cast<int>(logText.size()), nullptr, logText.data());
        LOG_INTERNAL_ERROR(logText.data());

        glDeleteShader(id);
        return false;
    }

    return true;
}
} // namespace GraphicLib::OpenGLImpl
