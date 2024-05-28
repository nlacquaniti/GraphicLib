#include "OpenGLImpl/RenderBufferImpl.h"

#include "FmtFormat.h"
#include "GraphicLib/Utilities/RenderBufferUtils.h"
#include "InternalLogger.h"
#include <glad/glad.h>
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
    const std::string& errorText = fmt::format("RenderBufferFormat {}", RenderBufferUtils::RenderBufferFormatToString(format));
    LOG_INTERNAL_ERROR(errorText.c_str());
    return false;
}
} // namespace

void RenderBufferImpl::Initialise(unsigned int& id) {
    glGenRenderbuffers(1, &id);
}

void RenderBufferImpl::Bind(unsigned int id) {
    glBindRenderbuffer(GL_RENDERBUFFER, id);
}

void RenderBufferImpl::Unbind(unsigned int /*unused*/) {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBufferImpl::Set(unsigned /*unused*/, const RenderBufferData& data) {
    unsigned int format{};
    if (!ConvertRenderBufferFormat(data.Format, format)) {
        return;
    }

    glRenderbufferStorage(GL_RENDERBUFFER, format, data.Width, data.Height);
}

void RenderBufferImpl::Delete(unsigned int& id) {
    glDeleteRenderbuffers(1, &id);
}
} // namespace GraphicLib::OpenGLImpl
