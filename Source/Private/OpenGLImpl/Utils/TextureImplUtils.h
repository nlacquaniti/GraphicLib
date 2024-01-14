#pragma once

#include "GraphicLib/Texture.h"

namespace GraphicLib {
namespace OpenGLImpl {
class TextureImplUtils {
public:
    static bool ConvertTextureType(ETextureType type, unsigned int& outType);
    static bool ConvertTextureParamName(ETextureParamName paramName, unsigned int& outParamName);
    static bool ConvertTextureParamValue(ETextureParamValue paramValue, int& outParamValue);
    static bool ConvertTextureChannel(ETextureChannel channel, unsigned int& outChannel);
    static bool ConvertTextureFormat(ETextureFormat format, int& outFormat);
    static bool ConvertTextureDataType(ETextureDataType dataType, unsigned int& outDataType);
    static bool ConvertTextureFormatToFrameBufferAttachment(ETextureFormat textureFormat, unsigned int& outFrameBufferAttachment);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
