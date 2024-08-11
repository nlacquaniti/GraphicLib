#include "OpenGLImpl/Utils/RenderBufferImplUtils.h"

#include "GraphicLib/Utilities/RenderBufferUtils.h"
#include "InternalLogger.h"
#include <glad/glad.h>
#include <format>
#include <string>

namespace GraphicLib::Internal {
bool ConvertRenderBufferFormatToFrameBufferAttachment(
    ERenderBufferFormat format, unsigned int& outFrameBufferAttachment) {
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

    const std::string& errorText = std::format(
        "RenderBufferFormat {}", RenderBufferUtils::RenderBufferFormatToString(format));
    LOG_INTERNAL_ERROR(errorText.c_str());
    return false;
}

bool ConvertRenderBufferFormatToInternalFormat(
    ERenderBufferFormat format, unsigned int& outFormat) {
    switch (format) {
    case ERenderBufferFormat::DEPTH16:
        outFormat = GL_DEPTH_COMPONENT16;
        return true;
    case ERenderBufferFormat::DEPTH24:
        outFormat = GL_DEPTH_COMPONENT24;
        return true;
    case ERenderBufferFormat::DEPTH32:
        outFormat = GL_DEPTH_COMPONENT32;
        return true;
    case ERenderBufferFormat::STENCIL8:
        outFormat = GL_STENCIL_INDEX8;
        return true;
    case ERenderBufferFormat::DEPTH24_STENCIL8:
        outFormat = GL_DEPTH24_STENCIL8;
        return true;
    case ERenderBufferFormat::NONE:
        break;
    }
    const std::string& errorText = std::format(
        "RenderBufferFormat {}", RenderBufferUtils::RenderBufferFormatToString(format));
    LOG_INTERNAL_ERROR(errorText.c_str());
    return false;
}
} // namespace GraphicLib::Internal
