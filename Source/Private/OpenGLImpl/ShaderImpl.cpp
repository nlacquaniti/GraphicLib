#include "OpenGLImpl/ShaderImpl.h"

#include "InternalLogger.h"
#include "OpenGLImpl/glad.h"
#include <vector>

namespace GraphicLib {
namespace OpenGLImpl {
namespace {
static bool _compileShader(unsigned int shaderID, unsigned int compilationType) {
    int success{};
    if (compilationType == GL_COMPILE_STATUS) {
        glGetShaderiv(shaderID, compilationType, &success);
    } else if (compilationType == GL_LINK_STATUS) {
        glGetProgramiv(shaderID, compilationType, &success);
    }
    if (!success) {
        int infoLogLength{};
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> logText{};
        logText.reserve(static_cast<size_t>(infoLogLength));
        glGetShaderInfoLog(shaderID, infoLogLength, &infoLogLength, logText.data());
        InternalLogger::Get().LogInternalError("ShaderImpl::Load", logText.data());
    }
    return success;
}
} // namespace

bool ShaderImpl::Load(unsigned int& id, const char* vertexShared, const char* fragmentShader) {
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShared, nullptr);
    glCompileShader(vertex);
    if (!_compileShader(vertex, GL_COMPILE_STATUS)) {
        glDeleteShader(vertex);
        return false;
    }

    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShader, nullptr);
    glCompileShader(fragment);
    if (!_compileShader(fragment, GL_COMPILE_STATUS)) {
        return false;
    }

    // shader Program
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    if (!_compileShader(id, GL_LINK_STATUS)) {
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        return false;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

void ShaderImpl::Bind(unsigned int id) {
    glUseProgram(id);
}

void ShaderImpl::Unbind(unsigned int) {
    glUseProgram(0);
}

void ShaderImpl::SetUniformValue(unsigned int id, const char* name, bool value) {
    Bind(id);
    glUniform1i(glGetUniformLocation(id, name), static_cast<int>(value));
}

void ShaderImpl::SetUniformValue(unsigned int id, const char* name, int value) {
    Bind(id);
    glUniform1i(glGetUniformLocation(id, name), value);
}

void ShaderImpl::SetUniformValue(unsigned int id, const char* name, float value) {
    Bind(id);
    glUniform1f(glGetUniformLocation(id, name), value);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
