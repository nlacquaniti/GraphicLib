#include "OpenGLImpl/RenderBufferImpl.h"

#include "GraphicLib/Utilities/RenderBufferUtils.h"
#include "InternalLogger.h"
#include <glad/glad.h>
#include <format>
#include <string>


namespace GraphicLib::OpenGLImpl {
namespace {
bool ConvertRenderBufferFormat(ERenderBufferFormat format, unsigned int& outFormat) {
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
    const std::string& errorText = std::format("RenderBufferFormat {}", RenderBufferUtils::RenderBufferFormatToString(format));
    LOG_INTERNAL_ERROR(errorText.c_str());
    return false;
}
} // namespace

void RenderBufferImpl::Initialise(unsigned int& id) const {
    glGenRenderbuffers(1, &id);
}

void RenderBufferImpl::Bind(unsigned int id) const {
    glBindRenderbuffer(GL_RENDERBUFFER, id);
}

void RenderBufferImpl::Unbind(unsigned int) const {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBufferImpl::Set(unsigned, const RenderBufferData& data) const {
    unsigned int format{};
    if (!ConvertRenderBufferFormat(data.Format, format)) {
        return;
    }

    glRenderbufferStorage(GL_RENDERBUFFER, format, data.Width, data.Height);
}

void RenderBufferImpl::Delete(unsigned int& id) const {
    glDeleteRenderbuffers(1, &id);
}
} // namespace GraphicLib::OpenGLImpl
