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

void VertexArrayImpl::DrawTriangles(unsigned int, int trianglesCount) const {
    glDrawElements(GL_TRIANGLES, trianglesCount, GL_UNSIGNED_INT, nullptr);
}

void VertexArrayImpl::DrawVertices(unsigned int id, int verticesCount) const {
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
