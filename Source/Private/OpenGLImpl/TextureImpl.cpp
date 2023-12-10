#include "OpenGLImpl/TextureImpl.h"

#include "GraphicLib/Utilities/TextureUtils.h"
#include "InternalLogger.h"
#include <glad/glad.h>
#include <sstream>

namespace GraphicLib {
namespace OpenGLImpl {
namespace {
bool ConvertTextureType(ETextureType type, unsigned int& outType) {
    switch (type) {
        case ETextureType::TEXTURE_2D:
            outType = GL_TEXTURE_2D;
            return true;
        case ETextureType::CUBE_MAP:
            outType = GL_TEXTURE_CUBE_MAP;
            return true;
        case ETextureType::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureType " << TextureUtils::TextureTypeToString(type);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}

bool ConvertTextureParamName(ETextureParamName paramName, unsigned int& outParamName) {
    switch (paramName) {
        case ETextureParamName::MIN_FILTER:
            outParamName = GL_TEXTURE_MIN_FILTER;
            return true;
        case ETextureParamName::MAG_FILTER:
            outParamName = GL_TEXTURE_MAG_FILTER;
            return true;
        case ETextureParamName::WRAP_S:
            outParamName = GL_TEXTURE_WRAP_S;
            return true;
        case ETextureParamName::WRAP_T:
            outParamName = GL_TEXTURE_WRAP_T;
            return true;
        case ETextureParamName::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureParamName " << TextureUtils::TextureParamNameToString(paramName);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}

bool ConvertTextureParamValue(ETextureParamValue paramValue, int& outParamValue) {
    switch (paramValue) {
        case ETextureParamValue::FILTER_NEAREST:
            outParamValue = GL_NEAREST;
            return true;
        case ETextureParamValue::FILTER_LIEAR:
            outParamValue = GL_LINEAR;
            return true;
        case ETextureParamValue::WRAP_CLAMP_TO_EDGE:
            outParamValue = GL_CLAMP_TO_EDGE;
            return true;
        case ETextureParamValue::WRAP_CLAMP_TO_BORDER:
            outParamValue = GL_CLAMP_TO_BORDER;
            return true;
        case ETextureParamValue::WRAP_MIRRORED_REPEAT:
            outParamValue = GL_MIRRORED_REPEAT;
            return true;
        case ETextureParamValue::WRAP_REPEAT:
            outParamValue = GL_REPEAT;
            return true;
        case ETextureParamValue::WRAP_MIRROR_CLAMP_TO_EDGE:
            outParamValue = GL_MIRROR_CLAMP_TO_EDGE;
            return true;
        case ETextureParamValue::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureParamValue " << TextureUtils::TextureParamValueToString(paramValue);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}

bool ConvertTextureChannel(ETextureChannel channel, unsigned int& outChannel) {
    switch (channel) {
        case ETextureChannel::GRAY:
            outChannel = GL_RED;
            return true;
        case ETextureChannel::GRAY_ALPHA:
            outChannel = GL_RG;
            return true;
        case ETextureChannel::RGB:
            outChannel = GL_RGB;
            return true;
        case ETextureChannel::RGBA:
            outChannel = GL_RGBA;
            return true;
        case ETextureChannel::STENCIL:
            outChannel = GL_STENCIL_INDEX;
            return true;
        case ETextureChannel::DEPTH:
            outChannel = GL_DEPTH_COMPONENT;
            return true;
        case ETextureChannel::DEPTH_STENCIL:
            outChannel = GL_DEPTH_STENCIL;
            return true;
        case ETextureChannel::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureChannel " << TextureUtils::TextureChannelToString(channel);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}

bool ConvertTextureFormat(ETextureFormat format, int& outFormat) {
    switch (format) {
        case ETextureFormat::RGBA8:
            outFormat = GL_RGBA8;
            return true;
        case ETextureFormat::RGBA16F:
            outFormat = GL_RGBA16F;
            return true;
        case ETextureFormat::RGBA32F:
            outFormat = GL_RGBA32F;
            return true;
        case ETextureFormat::SRGB8:
            outFormat = GL_SRGB8;
            return true;
        case ETextureFormat::SRGB8_ALPHA8:
            outFormat = GL_SRGB8_ALPHA8;
            return true;
        case ETextureFormat::DEPTH16:
            outFormat = GL_DEPTH_COMPONENT16;
            return true;
        case ETextureFormat::DEPTH24:
            outFormat = GL_DEPTH_COMPONENT24;
            return true;
        case ETextureFormat::DEPTH32F:
            outFormat = GL_DEPTH_COMPONENT32F;
            return true;
        case ETextureFormat::DEPTH24_STENCIL8:
            outFormat = GL_DEPTH24_STENCIL8;
            return true;
        case ETextureFormat::DEPTH32F_STENCIL8:
            outFormat = GL_DEPTH32F_STENCIL8;
            return true;
        case ETextureFormat::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureFormat " << TextureUtils::TextureFormatToString(format);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}

bool ConvertTextureDataType(ETextureDataType dataType, unsigned int& outDataType) {
    switch (dataType) {
        case ETextureDataType::UNSIGNED_BYTE:
            outDataType = GL_UNSIGNED_BYTE;
            return true;
        case ETextureDataType::FLOAT:
            outDataType = GL_FLOAT;
            return true;
        case ETextureDataType::HALF_FLOAT:
            outDataType = GL_HALF_FLOAT;
            return true;
        case ETextureDataType::UNSIGNED_SHORT:
            outDataType = GL_UNSIGNED_SHORT;
            return true;
        case ETextureDataType::INT:
            outDataType = GL_INT;
            return true;
        case ETextureDataType::UNSIGNED_INT:
            outDataType = GL_UNSIGNED_INT;
            return true;
        case ETextureDataType::UNSIGNED_INT_24_8:
            outDataType = GL_UNSIGNED_INT_24_8;
            return true;
        case ETextureDataType::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureDataType " << TextureUtils::TextureDataTypeToString(dataType);
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

void TextureImpl::Bind(unsigned int id, ETextureType type) const {
    unsigned int target{};
    if (!ConvertTextureType(type, target)) {
        return;
    }
    glBindTexture(target, id);
}

void TextureImpl::Unbind(unsigned int, ETextureType type) const {
    unsigned int target{};
    if (!ConvertTextureType(type, target)) {
        return;
    }
    glBindTexture(target, 0);
}

void TextureImpl::Draw(unsigned int id, ETextureType type, unsigned char slot) const {
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

    int internalFormat{};
    if (!ConvertTextureFormat(textureData.Format, internalFormat)) {
        return;
    }

    unsigned int textureFormat{};
    if (!ConvertTextureChannel(textureData.Channel, textureFormat)) {
        return;
    }

    unsigned int textureDataType{};
    if (!ConvertTextureDataType(textureData.DataType, textureDataType)) {
        return;
    }

    // Assign texture Parameters.
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

    glTexImage2D(target, 0, internalFormat, textureData.Width, textureData.Height, 0, textureFormat, textureDataType, textureData.PixelData.Data());
    glGenerateMipmap(target);
}

void TextureImpl::Delete(unsigned int& id, ETextureType type) const {
    Bind(id, type);
    glDeleteTextures(1, &id);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
