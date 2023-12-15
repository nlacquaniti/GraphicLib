#include "OpenGLImpl/Utils/RenderBufferImplUtils.h"

#include "GraphicLib/Utilities/RenderBufferUtils.h"
#include "InternalLogger.h"
#include <glad/glad.h>
#include <sstream>

namespace GraphicLib {
namespace OpenGLImpl {
bool RenderBufferImplUtils::ConvertRenderBufferFormatToFrameBufferAttachment(ERenderBufferFormat format, unsigned int& outFrameBufferAttachment) {
    switch (format) {
        case ERenderBufferFormat::DEPTH16:
        case ERenderBufferFormat::DEPTH24:
        case ERenderBufferFormat::DEPTH32:
            outFrameBufferAttachment = GL_DEPTH_ATTACHMENT;
            return true;
        case ERenderBufferFormat::STENCIL8:
            outFrameBufferAttachment = GL_STENCIL_ATTACHMENT;
            return true;
        case ERenderBufferFormat::DEPTH24_STENCIL8:
            outFrameBufferAttachment = GL_DEPTH_STENCIL_ATTACHMENT;
            return true;
        case ERenderBufferFormat::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "RenderBufferFormat " << RenderBufferUtils::RenderBufferFormatToString(format);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}
} // namespace OpenGLImpl
} // namespace GraphicLib
