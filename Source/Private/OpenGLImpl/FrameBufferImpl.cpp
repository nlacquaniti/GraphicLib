#include "OpenGLImpl/FrameBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib {
namespace OpenGLImpl {
void FrameBufferImpl::Initialise(unsigned int& id) const {
	glGenFramebuffers(1, &id);
}

void FrameBufferImpl::Bind(unsigned int id) const {
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void FrameBufferImpl::Unbind(unsigned int) const {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferImpl::Delete(unsigned int& id) const {
    glDeleteFramebuffers(1, &id);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
