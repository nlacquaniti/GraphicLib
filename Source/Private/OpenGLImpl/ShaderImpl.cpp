#include "OpenGLImpl/ShaderImpl.h"

#include "FmtFormat.h"
#include "GraphicLib/Utilities/ShaderUtils.h"
#include "InternalLogger.h"
#include "Utils/ShaderImplUtils.h"
#include <glad/glad.h>
#include <string>
#include <vector>

namespace GraphicLib::OpenGLImpl {
namespace {
bool _createShader(const ShaderData& shaderData, unsigned int& id) {
    unsigned int shaderType{};
    if (!ShaderImplUtils::ConvertShaderType(shaderData.Type, shaderType)) {
        const std::string& logText = fmt::format("Can't EShaderType {} to OpenGL shader type", ShaderUtils::ShaderTypeToString(shaderData.Type));
        LOG_INTERNAL_ERROR(logText.c_str());
        return false;
    }

    const std::string& shaderContent = ShaderImplUtils::LoadFromFile(shaderData.FilePath.c_str());
    if (shaderContent.empty()) {
        const std::string& logText = fmt::format("Can't open shader at path {}", shaderData.FilePath.c_str());
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
        int infoLogLength{};
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> logText{};
        logText.reserve(static_cast<size_t>(infoLogLength));
        glGetShaderInfoLog(id, infoLogLength, &infoLogLength, logText.data());
        LOG_INTERNAL_ERROR(logText.data());

        glDeleteShader(id);
        return false;
    }

    return true;
}
} // namespace

void ShaderImpl::Initialise(unsigned int& id) {
    id = glCreateProgram();
}

void ShaderImpl::Bind(unsigned int id) {
    glUseProgram(id);
}

void ShaderImpl::Unbind(unsigned int /*unused*/) {
    glUseProgram(0);
}

void ShaderImpl::Set(unsigned int id, const std::vector<ShaderData>& shadersData) {
    std::vector<unsigned int> shaderIDs{};
    shaderIDs.reserve(shadersData.size());

    for (const ShaderData& shaderData : shadersData) {
        unsigned int shaderID{};
        if (!_createShader(shaderData, shaderID)) {
            return;
        }

        shaderIDs.push_back(shaderID);
        glAttachShader(id, shaderID);
    }

    glLinkProgram(id);
    int successfullyCompiled{};
    glGetProgramiv(id, GL_LINK_STATUS, &successfullyCompiled);
    if (successfullyCompiled == 0) {
        int infoLogLength{};
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> logText{};
        logText.reserve(static_cast<size_t>(infoLogLength));
        glGetShaderInfoLog(id, infoLogLength, &infoLogLength, logText.data());
        LOG_INTERNAL_ERROR(logText.data());
    }

    for (unsigned int shaderID : shaderIDs) {
        glDeleteShader(shaderID);
    }
}

void ShaderImpl::SetUniformBoolValue(unsigned int id, const char* name, bool value) {
    glUniform1i(glGetUniformLocation(id, name), static_cast<int>(value));
}

void ShaderImpl::SetUniformIntValue(unsigned int id, const char* name, int value) {
    glUniform1i(glGetUniformLocation(id, name), value);
}

void ShaderImpl::SetUniformFloatValue(unsigned int id, const char* name, float value) {
    glUniform1f(glGetUniformLocation(id, name), value);
}

void ShaderImpl::SetUniformMat4Value(unsigned int id, const char* name, const float* value) {
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, value);
}

void ShaderImpl::Delete(unsigned int& id) {
    glDeleteProgram(id);
    id = 0;
}
} // namespace GraphicLib::OpenGLImpl
