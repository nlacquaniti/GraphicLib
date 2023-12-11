#include "OpenGLImpl/FrameBufferImpl.h"

#include "GraphicLib/Texture.h"
#include "InternalLogger.h"
#include <glad/glad.h>
#include <sstream>

namespace GraphicLib {
namespace OpenGLImpl {
namespace {
bool ConvertTextureFormatToFrameBufferAttachment(ETextureFormat textureFormat, int& outFrameBufferAttachment) {
    switch (textureFormat) {
        case ETextureFormat::RGBA:
        case ETextureFormat::RGB:
        case ETextureFormat::RGBA8:
        case ETextureFormat::RGBA16F:
        case ETextureFormat::RGBA32F:
        case ETextureFormat::SRGB8:
        case ETextureFormat::SRGB8_ALPHA8:
            outFrameBufferAttachment = GL_COLOR_ATTACHMENT0;
            return true;
        case ETextureFormat::DEPTH:
        case ETextureFormat::DEPTH16:
        case ETextureFormat::DEPTH24:
        case ETextureFormat::DEPTH32:
        case ETextureFormat::DEPTH32F:
            outFrameBufferAttachment = GL_DEPTH_ATTACHMENT;
            return true;
        case ETextureFormat::STENCIL:
        case ETextureFormat::STENCIL8:
            outFrameBufferAttachment = GL_STENCIL_ATTACHMENT;
            return true;
        case ETextureFormat::DEPTH24_STENCIL8:
        case ETextureFormat::DEPTH32F_STENCIL8:
            outFrameBufferAttachment = GL_DEPTH_STENCIL_ATTACHMENT;
            return true;
        case ETextureFormat::NONE:
            break;
    }
    std::stringstream errorText;
    errorText << "TextureFormat " << TextureUtils::TextureFormatToString(textureFormat);
    LOG_INTERNAL_ERROR(errorText.str().c_str());
    return false;
}
} // namespace
void FrameBufferImpl::Initialise(unsigned int& id) const {
    glGenFramebuffers(1, &id);
}

void FrameBufferImpl::Bind(unsigned int id) const {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FrameBufferImpl::Unbind(unsigned int) const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferImpl::Set(unsigned int, const TextureData& frameBufferTextureData) {
    int frameBufferAttachment{};
    if (!ConvertTextureFormatToFrameBufferAttachment(frameBufferTextureData.Format, frameBufferAttachment)) {
        return;
    }
    glFramebufferTexture2D(GL_FRAMEBUFFER,frameBufferAttachment, frameBufferAttachment.
}

void FrameBufferImpl::Delete(unsigned int& id) const {
    glDeleteFramebuffers(1, &id);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
