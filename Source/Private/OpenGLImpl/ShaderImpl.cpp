#ifndef MOCK_OPENGL_IMPL
#include "OpenGLImpl/ShaderImpl.h"

#include <glad/glad.h>

namespace GraphicLib::Internal {
namespace {
bool createShader(const Internal::ShaderParameter& shaderParameter,
    unsigned int* id,
    void (*onCompilationFailed)(const char*)) {
    *id = glCreateShader(shaderParameter.Type);
    glShaderSource(*id, 1, &shaderParameter.Content, nullptr);
    glCompileShader(*id);

    int successfullyCompiled;
    glGetShaderiv(*id, GL_COMPILE_STATUS, &successfullyCompiled);
    if (successfullyCompiled == 0) {
        static constexpr size_t MAX_TEXT_COUNT = 1024;
        char errorText[MAX_TEXT_COUNT];
        glGetShaderInfoLog(*id, static_cast<int>(MAX_TEXT_COUNT), nullptr, errorText);

        if (onCompilationFailed != nullptr) {
            onCompilationFailed(errorText);
        }

        glDeleteShader(*id);

        return false;
    }

    return true;
}
} // namespace

bool InitialiseShader(unsigned int* id,
    const Internal::ShaderData& data,
    size_t parametersCount,
    void (*onCompilationFailed)(const char*)) {
    if (parametersCount > Internal::ShaderData::MAX_PARAMETERS_COUNT) {
        return false;
    }

    *id = glCreateProgram();

    unsigned int shaderIDs[Internal::ShaderData::MAX_PARAMETERS_COUNT];
    for (size_t i = 0; i < parametersCount; ++i) {
        if (!createShader(data.Parameters[i], &shaderIDs[i], onCompilationFailed)) {
            return false;
        }

        glAttachShader(*id, shaderIDs[i]);
    }

    glLinkProgram(*id);

    int successfullyCompiled;
    glGetProgramiv(*id, GL_LINK_STATUS, &successfullyCompiled);
    if (successfullyCompiled == 0) {
        static constexpr size_t MAX_TEXT_COUNT = 1024;
        int errorTextLength;
        char errorText[MAX_TEXT_COUNT];
        glGetShaderInfoLog(*id, static_cast<int>(MAX_TEXT_COUNT), &errorTextLength, errorText);

        if (onCompilationFailed != nullptr) {
            onCompilationFailed(errorText);
        }
    }

    for (size_t i = 0; i < parametersCount; ++i) {
        glDeleteShader(shaderIDs[i]);
    }

    return successfullyCompiled == 1;
}

void BindShader(unsigned int id) {
    glUseProgram(id);
}

void UnbindShader() {
    glUseProgram(0);
}

void SetUniformBoolValueShader(unsigned int id, const char* name, bool value) {
    glUniform1i(glGetUniformLocation(id, name), static_cast<int>(value));
}

void SetUniformIntValueShader(unsigned int id, const char* name, int value) {
    glUniform1i(glGetUniformLocation(id, name), value);
}

void SetUniformFloatValueShader(unsigned int id, const char* name, float value) {
    glUniform1f(glGetUniformLocation(id, name), value);
}

void SetUniformMat4ValueShader(unsigned int id, const char* name, const float* value) {
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, value);
}

void DeleteShader(unsigned int* id) {
    glDeleteProgram(*id);
    *id = 0;
}
} // namespace GraphicLib::Internal
#endif