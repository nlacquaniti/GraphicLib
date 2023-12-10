#include "OpenGLImpl/FrameBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib {
namespace OpenGLImpl {
void FrameBufferImpl::Initialise(unsigned int& id) const {
	glGenFrameBuffers(1, &id);
}

void FrameBufferImpl::Bind(unsigned int id) const {
	glBindFrameBuffer(GL_FrameBuffer, id);
}

void FrameBufferImpl::Unbind(unsigned int) const {
	glBindFrameBuffer(GL_FrameBuffer, 0);
}

void FrameBufferImpl::Delete(unsigned int& id) const {
    glDeleteFrameBuffers(1, &id);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
