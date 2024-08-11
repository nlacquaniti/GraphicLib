#include "GraphicLib/Shader.h"

#include "GraphicLib/Utilities/ShaderUtils.h"
#include "InternalLogger.h"

#include "OpenGLImpl/ShaderImpl.h"
#include "OpenGLImpl/Utils/ShaderImplUtils.h"

#include <format>

namespace GraphicLib {
Shader::~Shader() noexcept {
    if (!_id.IsInitialised) {
        return;
    }

    Internal::DeleteShader(&_id.Value);
}

void Shader::Initialise(const std::span<const ShaderData>& data) {
    static_assert(MAX_DATA_COUNT == Internal::ShaderData::MAX_PARAMETERS_COUNT);

    if (_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Already initialised");
        return;
    }

    if (data.empty()) {
        LOG_INTERNAL_ERROR("Data is empty");
        return;
    }

    if (data.size() > MAX_DATA_COUNT) {
        const std::string logText =
            std::format("data.size() is greater then MAX_DATA_COUNT: {}", MAX_DATA_COUNT);
        LOG_INTERNAL_ERROR(logText.c_str());
        return;
    }

    for (std::size_t i = 0; i < data.size(); ++i) {
        const ShaderData& shader = data[i];
        if (shader.Type == EShaderType::NONE) {
            const std::string logText =
                std::format("data Shader.type::NONE at index {} ", i);
            LOG_INTERNAL_ERROR(logText.c_str());
            return;
        }

        if (shader.FilePath[0] == '\0') {
            const std::string logText = std::format(
                "Shader.type {} at index {} has empty file path Shader.FilePath",
                ShaderUtils::ShaderTypeToString(shader.Type), i);
            LOG_INTERNAL_ERROR(logText.c_str());
            return;
        }

        _data.at(i) = shader;
        ++_dataCount;
    }

    Internal::ShaderData internalShaderData;
    std::array<std::string, MAX_DATA_COUNT> shaderFilesContent;
    for (std::size_t i = 0; i < data.size(); ++i) {
        if (!Internal::ConvertShaderType(
                data[i].Type, internalShaderData.Parameters[i].Type)) {
            return;
        }

        shaderFilesContent.at(i) = Internal::LoadFromFile(_data[i].FilePath.data());
        if (shaderFilesContent.at(i).empty()) {
            return;
        }

        internalShaderData.Parameters[i].Content = shaderFilesContent.at(i).c_str();
    }

    if (!Internal::InitialiseShader(&_id.Value, internalShaderData, data.size(),
            [](const char* message) { LOG_INTERNAL_ERROR(message); })) {
        return;
    }

    _id.IsInitialised = true;
}

void Shader::Bind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::BindShader(_id.Value);
}

void Shader::Unbind() const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::UnbindShader();
}

void Shader::SetUniformBoolValue(const char* name, bool value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::SetUniformIntValueShader(_id.Value, name, static_cast<int>(value));
}

void Shader::SetUniformIntValue(const char* name, int value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::SetUniformIntValueShader(_id.Value, name, value);
}

void Shader::SetUniformFloatValue(const char* name, float value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::SetUniformFloatValueShader(_id.Value, name, value);
}

void Shader::SetUniformMat4Value(const char* name, float* value) const {
    if (!_id.IsInitialised) {
        LOG_INTERNAL_ERROR("Uninitialised");
        return;
    }

    Internal::SetUniformMat4ValueShader(_id.Value, name, value);
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
