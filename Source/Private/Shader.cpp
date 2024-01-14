#include "GraphicLib/Shader.h"

#include "InternalLogger.h"
#include "FmtFormat.h"
#include <string>

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
Shader::~Shader() {
    Delete();
}

void Shader::Initialise() {
    GraphicAPI::Get().GetShaderImpl().Initialise(_id);
}

void Shader::Bind() const {
    GraphicAPI::Get().GetShaderImpl().Bind(_id);
}

void Shader::Unbind() const {
    GraphicAPI::Get().GetShaderImpl().Unbind(_id);
}

void Shader::Set(const Span<ShaderParam>& params) {
    _data.Reserve(params.Size());
    for (Span<ShaderParam>::SizeType i = 0; i < params.Size(); ++i) {
        const ShaderParam& shader = params[i];
        if (shader.Type == EShaderType::NONE) {
            const std::string& logText = fmt::format("Shader.Type is NONE at index {}", i);
            LOG_INTERNAL_ERROR(logText.c_str());
            continue;
        }

        if (shader.FilePath.IsEmpty()) {
            const std::string& logText = fmt::format("Shader.FilePath is empty at index {}", i);
            LOG_INTERNAL_ERROR(logText.c_str());
            continue;
        }

        ShaderData shaderData{};
        shaderData.Type = shader.Type;
        shaderData.FilePath.SetData(shader.FilePath);
        _data.Add(shaderData);
    }

    GraphicAPI::Get().GetShaderImpl().Set(_id, GetData());
}

void Shader::SetUniformBoolValue(const char* name, bool value) const {
    Bind();
    GraphicAPI::Get().GetShaderImpl().SetUniformIntValue(_id, name, value);
}

void Shader::SetUniformIntValue(const char* name, int value) const {
    Bind();
    GraphicAPI::Get().GetShaderImpl().SetUniformIntValue(_id, name, value);
}

void Shader::SetUniformFloatValue(const char* name, float value) const {
    Bind();
    GraphicAPI::Get().GetShaderImpl().SetUniformFloatValue(_id, name, value);
}

void Shader::SetUniformMat4Value(const char* name, float* value) const {
    Bind();
    GraphicAPI::Get().GetShaderImpl().SetUniformMat4Value(_id, name, value);
}

void Shader::Delete() {
    GraphicAPI::Get().GetShaderImpl().Delete(_id);
}

Span<ShaderData> Shader::GetData() const {
    return { _data.Data(), _data.Size() };
}

unsigned int Shader::GetID() const {
    return _id;
}

} // namespace GraphicLib
