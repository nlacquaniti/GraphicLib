#include "OpenGLImpl/VertexArrayImpl.h"

#include <glad/glad.h>

namespace GraphicLib {
namespace OpenGLImpl {
void VertexArrayImpl::Initialise(unsigned int& id) const {
    glGenVertexArrays(1, &id);
}

void VertexArrayImpl::Bind(unsigned int id) const {
    glBindVertexArray(id);
}

void VertexArrayImpl::Unbind(unsigned int) const {
    glBindVertexArray(0);
}

void VertexArrayImpl::Draw(unsigned int, int trianglesCount) const {
    glDrawElements(GL_TRIANGLES, trianglesCount, GL_UNSIGNED_INT, nullptr);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
