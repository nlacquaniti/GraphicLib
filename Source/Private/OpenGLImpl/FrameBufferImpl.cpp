#include "OpenGLImpl/FrameBufferImpl.h"

#include "GraphicLib/RenderBuffer.h"
#include "GraphicLib/Texture.h"
#include "InternalLogger.h"
#include "Utils/RenderBufferImplUtils.h"
#include "Utils/TextureImplUtils.h"
#include <glad/glad.h>

namespace GraphicLib::OpenGLImpl {
void FrameBufferImpl::Initialise(unsigned int& id) const {
    glGenFramebuffers(1, &id);
}

void FrameBufferImpl::Bind(unsigned int id) const {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FrameBufferImpl::Unbind(unsigned int) const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferImpl::Set(unsigned int, const Texture& frameBufferTexture, const RenderBuffer& renderBuffer) const {
    // Set FrameBuffer Texture.
    unsigned int frameBufferAttachment{};
    if (!TextureImplUtils::ConvertTextureFormatToFrameBufferAttachment(frameBufferTexture.GetData().Format, frameBufferAttachment)) {
        return;
    }

    unsigned int textureTarget{};
    if (!TextureImplUtils::ConvertTextureType(frameBufferTexture.GetData().Type, textureTarget)) {
        return;
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, frameBufferAttachment, textureTarget, frameBufferTexture.GetID(), 0);

    // Set FrameBuffer RenderBuffer.
    unsigned int renderBufferAttachment{};
    if (!RenderBufferImplUtils::ConvertRenderBufferFormatToFrameBufferAttachment(renderBuffer.GetData().Format, renderBufferAttachment)) {
        return;
    }
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, renderBufferAttachment, GL_RENDERBUFFER, renderBuffer.GetID());

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOG_INTERNAL_ERROR("FrameBuffer is not completed");
    }
}

void FrameBufferImpl::Delete(unsigned int& id) const {
    glDeleteFramebuffers(1, &id);
}
} // namespace GraphicLib::OpenGLImpl
