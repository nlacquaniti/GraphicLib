#include "GraphicLib/Shader.h"

#include "GraphicLib/Utilities/ShaderUtils.h"
#include "InternalLogger.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

#include <format>

namespace GraphicLib {
Shader::~Shader() noexcept {
    if (!_id.IsInitialised) {
        return;
    }
    GraphicAPI::Get().GetShaderImpl().Delete(_id.Value);
}

void Shader::Initialise(const std::span<const ShaderData>& data) {
    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }

    if (data.empty()) {
        LOG_INTERNAL_ERROR("Data is empty");
        return;
    }

    if (data.size() > MAX_DATA_COUNT) {
        const std::string logText = std::format("data.size() is greater then MAX_DATA_COUNT: {}", MAX_DATA_COUNT);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    for (std::size_t i = 0; i < data.size(); ++i) {
        const ShaderData& shader = data[i];
        if (shader.Type == EShaderType::NONE) {
            const std::string logText = std::format("data Shader.type::NONE at index {} ", i);
            LOG_INTERNAL_ERROR(logText.c_str());
            return;
        }

        if (shader.FilePath[0] == '\0') {
            const std::string logText =
                std::format("Shader.type {} at index {} has empty file path Shader.FilePath", ShaderUtils::ShaderTypeToString(shader.Type), i);
            LOG_INTERNAL_ERROR(logText.c_str());
            return;
        }

        _data.at(i) = shader;
        ++_dataCount;
    }

    GraphicAPI::Get().GetShaderImpl().Initialise(_id.Value, data);
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

void Shader::SetUniformBoolValue(const char* name, bool value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetShaderImpl().SetUniformIntValue(_id.Value, name, static_cast<int>(value));
}

void Shader::SetUniformIntValue(const char* name, int value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetShaderImpl().SetUniformIntValue(_id.Value, name, value);
}

void Shader::SetUniformFloatValue(const char* name, float value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetShaderImpl().SetUniformFloatValue(_id.Value, name, value);
}

void Shader::SetUniformMat4Value(const char* name, float* value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }
    GraphicAPI::Get().GetShaderImpl().SetUniformMat4Value(_id.Value, name, value);
}

std::span<const ShaderData> Shader::GetData() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return {_data.data(), _dataCount};
}

unsigned int Shader::GetID() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
    }
    return _id.Value;
}
} // namespace GraphicLib
