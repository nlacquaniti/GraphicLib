#pragma once

#include "GraphicLib/RenderBuffer.h"

namespace GraphicLib::OpenGLImpl {
class RenderBufferImplUtils {
public:
    static bool ConvertRenderBufferFormatToFrameBufferAttachment(ERenderBufferFormat format, unsigned int& outFrameBufferAttachment);
};
} // namespace GraphicLib::OpenGLImpl
