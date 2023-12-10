#include "GraphicLib/Utilities/TextureUtils.h"

namespace GraphicLib {
const char* TextureUtils::TextureTypeToString(ETextureType textureType) {
    switch (textureType) {
        case ETextureType::NONE:
            return "NONE";
        case ETextureType::TEXTURE_2D:
            return "TEXTURE_2D";
        case ETextureType::CUBE_MAP:
            return "CUBE_MAP";
    }
    return "ERROR";
}

const char* TextureUtils::TextureParamNameToString(ETextureParamName paramName) {
    switch (paramName) {
        case ETextureParamName::NONE:
            return "NONE";
        case ETextureParamName::MIN_FILTER:
            return "MIN_FILTER";
        case ETextureParamName::MAG_FILTER:
            return "MAG_FILTER";
        case ETextureParamName::WRAP_S:
            return "WRAP_S";
        case ETextureParamName::WRAP_T:
            return "WRAP_T";
    }
    return "ERROR";
}

const char* TextureUtils::TextureParamValueToString(ETextureParamValue paramValue) {
    switch (paramValue) {
        case ETextureParamValue::NONE:
            return "NONE";
        case ETextureParamValue::FILTER_NEAREST:
            return "FILTER_NEAREST";
        case ETextureParamValue::FILTER_LIEAR:
            return "FILTER_LIEAR";
        case ETextureParamValue::WRAP_CLAMP_TO_EDGE:
            return "WRAP_CLAMP_TO_EDGE";
        case ETextureParamValue::WRAP_CLAMP_TO_BORDER:
            return "WRAP_CLAMP_TO_BORDER";
        case ETextureParamValue::WRAP_MIRRORED_REPEAT:
            return "WRAP_MIRRORED_REPEAT";
        case ETextureParamValue::WRAP_REPEAT:
            return "WRAP_REPEAT";
        case ETextureParamValue::WRAP_MIRROR_CLAMP_TO_EDGE:
            return "WRAP_MIRROR_CLAMP_TO_EDGE";
    }
    return "ERROR";
}

const char* TextureUtils::TextureChannelToString(ETextureChannel channel) {
    switch (channel) {
        case ETextureChannel::NONE:
            return "NONE";
        case ETextureChannel::GRAY:
            return "GRAY";
        case ETextureChannel::GRAY_ALPHA:
            return "GRAY_ALPHA";
        case ETextureChannel::RGB:
            return "RGB";
        case ETextureChannel::RGBA:
            return "RGBA";
        case ETextureChannel::STENCIL:
            return "STENCIL";
        case ETextureChannel::DEPTH:
            return "DEPTH";
        case ETextureChannel::DEPTH_STENCIL:
            return "DEPTH_STENCIL";
    }
    return "ERROR";
}

const char* TextureUtils::TextureFormatToString(ETextureFormat format) {
    switch (format) {
        case ETextureFormat::NONE:
            return "NONE";
        case ETextureFormat::RGBA8:
            return "RGBA8";
        case ETextureFormat::RGBA16F:
            return "RGBA16F";
        case ETextureFormat::RGBA32F:
            return "RGBA32F";
        case ETextureFormat::SRGB8:
            return "SRGB8";
        case ETextureFormat::SRGB8_ALPHA8:
            return "SRGB8_ALPHA8";
        case ETextureFormat::DEPTH16:
            return "DEPTH16";
        case ETextureFormat::DEPTH24:
            return "DEPTH24";
        case ETextureFormat::DEPTH32F:
            return "DEPTH32F";
        case ETextureFormat::DEPTH24_STENCIL8:
            return "DEPTH24_STENCIL8";
        case ETextureFormat::DEPTH32F_STENCIL8:
            return "DEPTH32F_STENCIL8";
    }
    return "ERROR";
}

const char* TextureUtils::TextureDataTypeToString(ETextureDataType dataType) {
    switch (dataType) {
        case ETextureDataType::NONE:
            return "NONE";
        case ETextureDataType::UNSIGNED_BYTE:
            return "UNSIGNED_BYTE";
        case ETextureDataType::FLOAT:
            return "FLOAT";
        case ETextureDataType::HALF_FLOAT:
            return "HALF_FLOAT";
        case ETextureDataType::UNSIGNED_SHORT:
            return "UNSIGNED_SHORT";
        case ETextureDataType::INT:
            return "INT";
        case ETextureDataType::UNSIGNED_INT:
            return "UNSIGNED_INT";
        case ETextureDataType::UNSIGNED_INT_24_8:
            return "UNSIGNED_INT_24_8";
    }
    return "ERROR";
}

} // namespace GraphicLib
