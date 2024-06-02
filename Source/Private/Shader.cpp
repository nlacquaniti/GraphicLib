#include "GraphicLib/Shader.h"

#include "FmtFormat.h"
#include "InternalLogger.h"
#include <string>

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
Shader::~Shader() noexcept {
    if (!_id.IsInitialised) {
        return;
    }
    GraphicAPI::Get().GetShaderImpl().Delete(_id.Value);
}

void Shader::Initialise() {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already Initialised");
        return;
    }
    GraphicAPI::Get().GetShaderImpl().Initialise(_id.Value);
    _id.IsInitialised = true;
}

void Shader::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetShaderImpl().Bind(_id.Value);
}

void Shader::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetShaderImpl().Unbind(_id.Value);
}

void Shader::Set(std::vector<ShaderData>&& data) {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    _data = std::move(data);
    for (size_t i = 0; i < _data.size(); ++i) {
        const ShaderData& shader = _data[i];
        if (shader.Type == EShaderType::NONE) {
            const std::string& logText = fmt::format("Shader.Type is NONE at index {}", i);
            LOG_INTERNAL_ERROR(logText.c_str());
        }

        if (shader.FilePath.empty()) {
            const std::string& logText = fmt::format("Shader.FilePath is empty at index {}", i);
            LOG_INTERNAL_ERROR(logText.c_str());
        }
    }

    GraphicAPI::Get().GetShaderImpl().Set(_id.Value, _data);
}

void Shader::SetUniformBoolValue(const char* name, bool value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Bind();
    GraphicAPI::Get().GetShaderImpl().SetUniformIntValue(_id.Value, name, static_cast<int>(value));
}

void Shader::SetUniformIntValue(const char* name, int value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Bind();
    GraphicAPI::Get().GetShaderImpl().SetUniformIntValue(_id.Value, name, value);
}

void Shader::SetUniformFloatValue(const char* name, float value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Bind();
    GraphicAPI::Get().GetShaderImpl().SetUniformFloatValue(_id.Value, name, value);
}

void Shader::SetUniformMat4Value(const char* name, float* value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Bind();
    GraphicAPI::Get().GetShaderImpl().SetUniformMat4Value(_id.Value, name, value);
}

const std::vector<ShaderData>& Shader::GetData() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _data;
}

unsigned int Shader::GetID() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _id.Value;
}
} // namespace GraphicLib
