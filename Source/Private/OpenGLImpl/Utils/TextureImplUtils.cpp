#include "OpenGLImpl/Utils/TextureImplUtils.h"

#include "GraphicLib/Texture.h"
#include "GraphicLib/Utilities/TextureUtils.h"
#include "InternalLogger.h"
#include "OpenGLImpl/TextureImpl.h"
#include <glad/glad.h>
#include <format>
#include <span>
#include <string>

namespace GraphicLib::Internal {
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
    const std::string& errorText =
        std::format("TextureType {}", TextureUtils::TextureTypeToString(type));
    LOG_INTERNAL_ERROR(errorText.c_str());
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
    const std::string& errorText = std::format(
        "TextureParamName {}", TextureUtils::TextureParamNameToString(paramName));
    LOG_INTERNAL_ERROR(errorText.c_str());
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
    const std::string& errorText = std::format(
        "TextureParamValue {}", TextureUtils::TextureParamValueToString(paramValue));
    LOG_INTERNAL_ERROR(errorText.c_str());
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
    const std::string& errorText =
        std::format("TextureChannel {}", TextureUtils::TextureChannelToString(channel));
    LOG_INTERNAL_ERROR(errorText.c_str());
    return false;
}

bool ConvertTextureFormat(ETextureFormat format, int& outFormat) {
    switch (format) {
    case ETextureFormat::RGBA:
        outFormat = GL_RGBA;
        return true;
    case ETextureFormat::RGB:
        outFormat = GL_RGB;
        return true;
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
    case ETextureFormat::DEPTH:
        outFormat = GL_DEPTH;
        return true;
    case ETextureFormat::DEPTH16:
        outFormat = GL_DEPTH_COMPONENT16;
        return true;
    case ETextureFormat::DEPTH24:
        outFormat = GL_DEPTH_COMPONENT24;
        return true;
    case ETextureFormat::DEPTH32:
        outFormat = GL_DEPTH_COMPONENT32;
        return true;
    case ETextureFormat::DEPTH32F:
        outFormat = GL_DEPTH_COMPONENT32F;
        return true;
    case ETextureFormat::STENCIL:
        outFormat = GL_STENCIL_INDEX;
        return true;
    case ETextureFormat::STENCIL8:
        outFormat = GL_STENCIL_INDEX8;
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
    const std::string& errorText =
        std::format("TextureFormat {}", TextureUtils::TextureFormatToString(format));
    LOG_INTERNAL_ERROR(errorText.c_str());
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
    const std::string& errorText = std::format(
        "TextureDataType {}", TextureUtils::TextureDataTypeToString(dataType));
    LOG_INTERNAL_ERROR(errorText.c_str());
    return false;
}

bool ConvertTextureFormatToFrameBufferAttachment(
    ETextureFormat textureFormat, unsigned int& outFrameBufferAttachment) {
    switch (textureFormat) {
    case ETextureFormat::RGBA:
    case ETextureFormat::RGB:
    case ETextureFormat::RGBA8:
    case ETextureFormat::RGBA16F:
    case ETextureFormat::RGBA32F:
    case ETextureFormat::SRGB8:
    case ETextureFormat::SRGB8_ALPHA8:
        outFrameBufferAttachment = GL_COLOR_ATTACHMENT0;
        return true;
    case ETextureFormat::DEPTH:
    case ETextureFormat::DEPTH16:
    case ETextureFormat::DEPTH24:
    case ETextureFormat::DEPTH32:
    case ETextureFormat::DEPTH32F:
        outFrameBufferAttachment = GL_DEPTH_ATTACHMENT;
        return true;
    case ETextureFormat::STENCIL:
    case ETextureFormat::STENCIL8:
        outFrameBufferAttachment = GL_STENCIL_ATTACHMENT;
        return true;
    case ETextureFormat::DEPTH24_STENCIL8:
    case ETextureFormat::DEPTH32F_STENCIL8:
        outFrameBufferAttachment = GL_DEPTH_STENCIL_ATTACHMENT;
        return true;
    case ETextureFormat::NONE:
        break;
    }
    const std::string& errorText = std::format(
        "TextureFormat {}", TextureUtils::TextureFormatToString(textureFormat));
    LOG_INTERNAL_ERROR(errorText.c_str());
    return false;
}
bool ConvertTextureData(
    const GraphicLib::TextureData& textureData, Internal::TextureData& outTextureData) {
    for (size_t i = 0; i < GraphicLib::TextureData::TEXTURE_PARAMETER_MAX_COUNT; ++i) {
        const GraphicLib::TextureParameter& textureParameter = textureData.Parameters[i];
        Internal::TextureParameter& internalTextureParameter =
            outTextureData.Parameters[i];

        if (!ConvertTextureParamName(
                textureParameter.Name, internalTextureParameter.Name)) {
            return false;
        }

        if (!ConvertTextureParamValue(
                textureParameter.Value, internalTextureParameter.Value)) {
            return false;
        }
    }

    outTextureData.PixelData = textureData.PixelData;

    if (!ConvertTextureType(textureData.Type, outTextureData.Type)) {
        return false;
    }

    if (!ConvertTextureChannel(textureData.Channel, outTextureData.TextureFormat)) {
        return false;
    }

    if (!ConvertTextureDataType(textureData.DataType, outTextureData.DataType)) {
        return false;
    }

    if (!ConvertTextureFormat(textureData.Format, outTextureData.Format)) {
        return false;
    }

    outTextureData.Width = textureData.Width;
    outTextureData.Height = textureData.Height;

    return true;
}
} // namespace GraphicLib::Internal
