#include "OpenGLImpl/VertexArrayImpl.h"

#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
void VertexArrayImpl::Initialise(unsigned int& id) {
    glGenVertexArrays(1, &id);
}

void VertexArrayImpl::Bind(unsigned int id) {
    glBindVertexArray(id);
}

void VertexArrayImpl::Unbind(unsigned int) {
    glBindVertexArray(0);
}

void VertexArrayImpl::Draw(unsigned int, int trianglesCount) {
    glDrawElements(GL_TRIANGLES, trianglesCount, GL_UNSIGNED_INT, nullptr);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
