#include "GraphicLib/Shader.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
bool Shader::Load(const char* vertexShared, const char* fragmentShader) {
    return GraphicAPI::Get().GetShaderImpl().Load(_id, vertexShared, fragmentShader);
}

void Shader::Bind() {
    GraphicAPI::Get().GetShaderImpl().Bind(_id);
}

void Shader::Unbind() {
    GraphicAPI::Get().GetShaderImpl().Unbind(_id);
}

void Shader::SetUniformBoolValue(const char* name, bool value) const {
    GraphicAPI::Get().GetShaderImpl().SetUniformIntValue(_id, name, value);
}

void Shader::SetUniformIntValue(const char* name, int value) const {
    GraphicAPI::Get().GetShaderImpl().SetUniformIntValue(_id, name, value);
}

void Shader::SetUniformFloatValue(const char* name, float value) const {
    GraphicAPI::Get().GetShaderImpl().SetUniformFloatValue(_id, name, value);
}

void Shader::SetUniformMat4Value(const char* name, float* value) const {
    GraphicAPI::Get().GetShaderImpl().SetUniformMat4Value(_id, name, value);
}
} // namespace GraphicLib
