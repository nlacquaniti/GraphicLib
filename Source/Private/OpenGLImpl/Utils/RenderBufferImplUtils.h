#pragma once

#include "GraphicLib/RenderBuffer.h"

namespace GraphicLib {
namespace OpenGLImpl {
class RenderBufferImplUtils {
public:
    static bool ConvertRenderBufferFormatToFrameBufferAttachment(ERenderBufferFormat format, unsigned int& outFrameBufferAttachment);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
