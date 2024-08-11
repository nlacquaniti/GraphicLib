#ifndef MOCK_OPENGL_IMPL
#include "OpenGLImpl/RenderBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib::Internal {
void InitialiseRenderBuffer(unsigned int* id) {
    glGenRenderbuffers(1, id);
}

void BindRenderBuffer(unsigned int id) {
    glBindRenderbuffer(GL_RENDERBUFFER, id);
}

void UnbindRenderBuffer() {
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void SetRenderBuffer(unsigned int format, int width, int height) {
    glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}

void DeleteRenderBuffer(unsigned int* id) {
    glDeleteRenderbuffers(1, id);
}
} // namespace GraphicLib::Internal
#endif