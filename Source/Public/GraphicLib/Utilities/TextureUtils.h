#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Texture.h"

namespace GraphicLib {
class DLL_API TextureUtils final {
public:
    static const char* TextureTypeToString(ETextureType textureType);
    static const char* TextureParamNameToString(ETextureParamName paramName);
    static const char* TextureParamValueToString(ETextureParamValue paramValue);
    static const char* TextureChannelToString(ETextureChannel channel);
    static const char* TextureFormatToString(ETextureFormat format);
    static const char* TextureDataTypeToString(ETextureDataType dataType);
};
} // namespace GraphicLib
