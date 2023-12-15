#include "GraphicLib/Utilities/RenderBufferUtils.h"

namespace GraphicLib {
const char* RenderBufferUtils::RenderBufferFormatToString(ERenderBufferFormat renderBufferFormat) {
    switch (renderBufferFormat) {
        case ERenderBufferFormat::NONE:
            return "NONE";
        case ERenderBufferFormat::DEPTH16:
            return "DEPTH16";
        case ERenderBufferFormat::DEPTH24:
            return "DEPTH24";
        case ERenderBufferFormat::DEPTH32:
            return "DEPTH32";
        case ERenderBufferFormat::STENCIL8:
            return "STENCIL8";
        case ERenderBufferFormat::DEPTH24_STENCIL8:
            return "DEPTH24_STENCIL8";
    }
    return "ERROR";
}
} // namespace GraphicLib
