#include "GraphicLib/Shader.h"

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/ShaderImpl.h"
using ShaderImpl = GraphicLib::OpenGLImpl::ShaderImpl;
#else
#error "No ShaderImpl has been detected."
#endif

namespace GraphicLib {
Shader* Shader::Create() {
    return new ShaderImpl();
}

bool Shader::Load(const char* vertexShared, const char* fragmentShader) {
    return _load(vertexShared, fragmentShader);
}

void Shader::Bind() {
    _bind();
}

void Shader::Unbind() {
    _unbind();
}

unsigned int Shader::GetID() const {
    return _getID();
}

void Shader::SetUniformValue(const char* name, int value) const {
    _setUniformValue(name, value);
}
} // namespace GraphicLib
