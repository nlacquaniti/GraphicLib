#pragma once

#include "GraphicLib/Texture.h"
#include "OpenGLImpl/TextureImpl.h"

namespace GraphicLib::Internal {
bool ConvertTextureType(ETextureType type, unsigned int& outType);
bool ConvertTextureParamName(ETextureParamName paramName, unsigned int& outParamName);
bool ConvertTextureParamValue(ETextureParamValue paramValue, int& outParamValue);
bool ConvertTextureChannel(ETextureChannel channel, unsigned int& outChannel);
bool ConvertTextureFormat(ETextureFormat format, int& outFormat);
bool ConvertTextureDataType(ETextureDataType dataType, unsigned int& outDataType);
bool ConvertTextureFormatToFrameBufferAttachment(
    ETextureFormat textureFormat, unsigned int& outFrameBufferAttachment);
bool ConvertTextureData(
    const GraphicLib::TextureData& textureData, Internal::TextureData& outTextureData);
} // namespace GraphicLib::Internal
