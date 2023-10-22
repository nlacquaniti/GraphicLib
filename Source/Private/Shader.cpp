#include "GraphicLib/Shader.h"

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/ShaderImpl.h"
using ShaderImpl = GraphicLib::OpenGLImpl::ShaderImpl;
#else
#error "No ShaderImpl has been detected."
#endif

namespace GraphicLib {
bool Shader::Load(const char* vertexShared, const char* fragmentShader) {
    return ShaderImpl::Load(_id, vertexShared, fragmentShader);
}

void Shader::Bind() {
    ShaderImpl::Bind(_id);
}

void Shader::Unbind() {
    ShaderImpl::Unbind(_id);
}

void Shader::SetUniformValue(const char* name, bool value) const {
    ShaderImpl::SetUniformValue(_id, name, value);
}

void Shader::SetUniformValue(const char* name, int value) const {
    ShaderImpl::SetUniformValue(_id, name, value);
}

void Shader::SetUniformValue(const char* name, float value) const {
    ShaderImpl::SetUniformValue(_id, name, value);
}
} // namespace GraphicLib
