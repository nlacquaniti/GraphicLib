#ifndef MOCK_OPENGL_IMPL
#include "OpenGLImpl/IndexBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib::Internal {
void InitialiseIndexBuffer(unsigned int* id) {
    glGenBuffers(1, id);
}

void BindIndexBuffer(unsigned int id) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void UnbindIndexBuffer() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SetIndexBuffer(const unsigned int* indicies, size_t indiciesCount) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        static_cast<long long>(indiciesCount * sizeof(unsigned int)), indicies,
        GL_STATIC_DRAW);
}

void DeleteIndexBuffer(unsigned int* id) {
    glDeleteBuffers(1, id);
}
} // namespace GraphicLib::Internal
#endif