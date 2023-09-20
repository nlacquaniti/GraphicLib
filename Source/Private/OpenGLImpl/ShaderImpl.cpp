#include "OpenGLImpl/ShaderImpl.h"

#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
namespace {
static bool _compileShader(unsigned int shaderID, unsigned int compilationType) {
    int success{};
    glGetShaderiv(shaderID, compilationType, &success);
    if (!success) {
        return false;
    }
    return true;
}
} // namespace

bool ShaderImpl::_load(const char* vertexShared, const char* fragmentShader) {
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShared, nullptr);
    glCompileShader(vertex);
    if (!_compileShader(vertex, GL_COMPILE_STATUS)) {
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
    _id = glCreateProgram();
    glAttachShader(_id, vertex);
    glAttachShader(_id, fragment);
    glLinkProgram(_id);
    if (!_compileShader(_id, GL_LINK_STATUS)) {
        return false;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}

void ShaderImpl::_bind() {
    glUseProgram(_id);
}

void ShaderImpl::_unbind() {
    glUseProgram(0);
}

unsigned int ShaderImpl::_getID() const {
    return _id;
}

void ShaderImpl::_setUniformValue(const char* name, int value) const {
    glUniform1i(glGetUniformLocation(_id, name), value);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
