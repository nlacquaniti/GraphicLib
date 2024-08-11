#pragma once

#include "GraphicLib/RenderBuffer.h"

namespace GraphicLib::Internal {
bool ConvertRenderBufferFormatToFrameBufferAttachment(
    ERenderBufferFormat format, unsigned int& outFrameBufferAttachment);
bool ConvertRenderBufferFormatToInternalFormat(
    ERenderBufferFormat format, unsigned int& outFormat);
} // namespace GraphicLib::Internal
