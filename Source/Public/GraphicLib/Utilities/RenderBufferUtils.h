#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/RenderBuffer.h"

namespace GraphicLib {
class DLL_API RenderBufferUtils {
public:
    static const char* RenderBufferFormatToString(ERenderBufferFormat renderBufferFormat);
};
} // namespace GraphicLib
