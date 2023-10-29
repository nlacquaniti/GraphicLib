#pragma once

#include "GraphicLib/Texture.h"

#include "GraphicLib/DLL_API.h"

namespace GraphicLib {
class DLL_API TextureUtils final {
public:
    static const char* TextureTypeToString(TextureType textureType);
    static const char* TextureParamNameToString(TextureParamName paramName);
    static const char* TextureParamValueToString(TextureParamValue paramValue);
    static const char* TextureChannelToString(TextureChannel channel);
};
} // namespace GraphicLib
