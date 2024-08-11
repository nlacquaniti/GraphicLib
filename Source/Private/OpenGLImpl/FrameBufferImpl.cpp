#ifndef MOCK_OPENGL_IMPL
#include "OpenGLImpl/FrameBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib::Internal {
void InitialiseFrameBuffer(unsigned int* id) {
    glGenFramebuffers(1, id);
}

void BindFrameBuffer(unsigned int id) {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void UnbindFrameBuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool SetFrameBuffer(unsigned int textureId,
    unsigned int frameBufferAttachement,
    unsigned int textureType,
    unsigned int renderBufferId,
    unsigned int renderBufferAttachment) {
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, frameBufferAttachement, textureType, textureId, 0);

    glFramebufferRenderbuffer(
        GL_FRAMEBUFFER, renderBufferAttachment, GL_RENDERBUFFER, renderBufferId);

    return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
}

void DeleteFrameBuffer(unsigned int* id) {
    glDeleteFramebuffers(1, id);
}
} // namespace GraphicLib::Internal
#endif