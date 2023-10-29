#include "GraphicLib/Utilities/TextureUtils.h"

namespace GraphicLib {
const char* TextureUtils::TextureTypeToString(TextureType textureType) {
    switch (textureType) {
        case TextureType::NONE:
            return "NONE";
        case TextureType::TEXTURE_2D:
            return "TEXTURE_2D";
        case TextureType::CUBE_MAP:
            return "CUBE_MAP";
    }
    return "ERROR";
}

const char* TextureUtils::TextureParamNameToString(TextureParamName paramName) {
    switch (paramName) {
        case TextureParamName::NONE:
            return "NONE";
        case TextureParamName::MIN_FILTER:
            return "MIN_FILTER";
        case TextureParamName::MAG_FILTER:
            return "MAG_FILTER";
        case TextureParamName::WRAP_S:
            return "WRAP_S";
        case TextureParamName::WRAP_T:
            return "WRAP_T";
    }
    return "ERROR";
}

const char* TextureUtils::TextureParamValueToString(TextureParamValue paramValue) {
    switch (paramValue) {
        case TextureParamValue::NONE:
            return "NONE";
        case TextureParamValue::FILTER_NEAREST:
            return "FILTER_NEAREST";
        case TextureParamValue::FILTER_LIEAR:
            return "FILTER_LIEAR";
        case TextureParamValue::WRAP_CLAMP_TO_EDGE:
            return "WRAP_CLAMP_TO_EDGE";
        case TextureParamValue::WRAP_CLAMP_TO_BORDER:
            return "WRAP_CLAMP_TO_BORDER";
        case TextureParamValue::WRAP_MIRRORED_REPEAT:
            return "WRAP_MIRRORED_REPEAT";
        case TextureParamValue::WRAP_REPEAT:
            return "WRAP_REPEAT";
        case TextureParamValue::WRAP_MIRROR_CLAMP_TO_EDGE:
            return "WRAP_MIRROR_CLAMP_TO_EDGE";
    }
    return "ERROR";
}

const char* TextureUtils::TextureChannelToString(TextureChannel channel) {
    switch (channel) {
        case TextureChannel::NONE:
            return "NONE";
        case TextureChannel::GRAY:
            return "GRAY";
        case TextureChannel::GRAY_ALPHA:
            return "GRAY_ALPHA";
        case TextureChannel::RGB:
            return "RGB";
        case TextureChannel::RGBA:
            return "RGBA";
    }
    return "ERROR";
}

} // namespace GraphicLib
