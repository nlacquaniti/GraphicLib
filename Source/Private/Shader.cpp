#include "GraphicLib/Shader.h"

#ifdef OPENGL_IMPL
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

void Shader::SetUniformBoolValue(const char* name, bool value) const {
    ShaderImpl::SetUniformIntValue(_id, name, value);
}

void Shader::SetUniformIntValue(const char* name, int value) const {
    ShaderImpl::SetUniformIntValue(_id, name, value);
}

void Shader::SetUniformFloatValue(const char* name, float value) const {
    ShaderImpl::SetUniformFloatValue(_id, name, value);
}

void Shader::SetUniformMat4Value(const char* name, float* value) const {
    ShaderImpl::SetUniformMat4Value(_id, name, value);
}
} // namespace GraphicLib
