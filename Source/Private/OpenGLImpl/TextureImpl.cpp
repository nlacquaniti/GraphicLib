#include "OpenGLImpl/TextureImpl.h"

#include "InternalLogger.h"
#include "GraphicLib/Utilities/TextureUtils.h"
#include <glad/glad.h>
#include <sstream>

namespace GraphicLib {
namespace OpenGLImpl {
namespace {
bool ConvertTextureType(TextureType type, unsigned int& outType) {
    switch (type) {
        case TextureType::TEXTURE_2D:
            outType = GL_TEXTURE_2D;
            return true;
        case TextureType::CUBE_MAP:
            outType = GL_TEXTURE_CUBE_MAP;
            return true;
        case TextureType::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureType " << TextureUtils::TextureTypeToString(type);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}

bool ConvertTextureParamName(TextureParamName paramName, unsigned int& outParamName) {
    switch (paramName) {
        case TextureParamName::MIN_FILTER:
            outParamName = GL_TEXTURE_MIN_FILTER;
            return true;
        case TextureParamName::MAG_FILTER:
            outParamName = GL_TEXTURE_MAG_FILTER;
            return true;
        case TextureParamName::WRAP_S:
            outParamName = GL_TEXTURE_WRAP_S;
            return true;
        case TextureParamName::WRAP_T:
            outParamName = GL_TEXTURE_WRAP_T;
            return true;
        case TextureParamName::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureParamName " << TextureUtils::TextureParamNameToString(paramName);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}

bool ConvertTextureParamValue(TextureParamValue paramValue, int& outParamValue) {
    switch (paramValue) {
        case TextureParamValue::FILTER_NEAREST:
            outParamValue = GL_NEAREST;
            return true;
        case TextureParamValue::FILTER_LIEAR:
            outParamValue = GL_LINEAR;
            return true;
        case TextureParamValue::WRAP_CLAMP_TO_EDGE:
            outParamValue = GL_CLAMP_TO_EDGE;
            return true;
        case TextureParamValue::WRAP_CLAMP_TO_BORDER:
            outParamValue = GL_CLAMP_TO_BORDER;
            return true;
        case TextureParamValue::WRAP_MIRRORED_REPEAT:
            outParamValue = GL_MIRRORED_REPEAT;
            return true;
        case TextureParamValue::WRAP_REPEAT:
            outParamValue = GL_REPEAT;
            return true;
        case TextureParamValue::WRAP_MIRROR_CLAMP_TO_EDGE:
            outParamValue = GL_MIRROR_CLAMP_TO_EDGE;
            return true;
        case TextureParamValue::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureParamValue " << TextureUtils::TextureParamValueToString(paramValue);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}

bool ConvertTextureChannel(TextureChannel channel, unsigned int& outChannel) {
    switch (channel) {
        case TextureChannel::GRAY:
            outChannel = GL_RED;
            return true;
        case TextureChannel::GRAY_ALPHA:
            outChannel = GL_RG;
            return true;
        case TextureChannel::RGB:
            outChannel = GL_RGB;
            return true;
        case TextureChannel::RGBA:
            outChannel = GL_RGBA;
            return true;
        case TextureChannel::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureChannel " << TextureUtils::TextureChannelToString(channel);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}
} // namespace

int TextureImpl::_maxTextureSlots{-1};

void TextureImpl::Initialise(unsigned int& id) const {
    if (_maxTextureSlots == -1) {
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextureSlots);
        std::stringstream logText;
        logText << "Max number of texture slots " << _maxTextureSlots;
        LOG_INTERNAL_NOTIFICATION(logText.str().c_str());
    }
    glGenTextures(1, &id);
}

void TextureImpl::Bind(unsigned int id, TextureType type) const {
    unsigned int target{};
    if (!ConvertTextureType(type, target)) {
        return;
    }
    glBindTexture(target, id);
}

void TextureImpl::Unbind(unsigned int, TextureType type) const {
    unsigned int target{};
    if (!ConvertTextureType(type, target)) {
        return;
    }
    glBindTexture(target, 0);
}

void TextureImpl::Draw(unsigned int id, TextureType type, unsigned char slot) const {
    if (slot > _maxTextureSlots) {
        std::stringstream logText;
        logText << "Provided texture slot " << slot << " exceeded the max number of texture slots " << _maxTextureSlots;
        LOG_INTERNAL_ERROR(logText.str().c_str());
        return;
    }
    glActiveTexture(GL_TEXTURE0 + slot);
    Bind(id, type);
}

void TextureImpl::Set(unsigned int id, const TextureData& textureData) const {
    Bind(id, textureData.Type);

    unsigned int target{};
    if (!ConvertTextureType(textureData.Type, target)) {
        return;
    }

    unsigned int textureFormat{};
    if (!ConvertTextureChannel(textureData.Channel, textureFormat)) {
        return;
    }

    for (unsigned long long i{}; i < textureData.Parameters.Size(); ++i) {
        const TextureParam& param = textureData.Parameters[i];

        unsigned int paramName{};
        if (!ConvertTextureParamName(param.Name, paramName)) {
            return;
        }

        int paramValue{};
        if (!ConvertTextureParamValue(param.Value, paramValue)) {
            return;
        }

        glTexParameteri(target, paramName, paramValue);
    }

    glTexImage2D(target, 0, GL_RGBA32F, textureData.Width, textureData.Height, 0, textureFormat, GL_UNSIGNED_BYTE, textureData.PixelData.Data());
    glGenerateMipmap(target);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
