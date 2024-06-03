#include "OpenGLImpl/VertexArrayImpl.h"

#include <glad/glad.h>

namespace GraphicLib::OpenGLImpl {
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

void VertexArrayImpl::DrawVertices(unsigned int, int verticesCount) const {
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void VertexArrayImpl::Delete(unsigned int& id) const {
    glDeleteVertexArrays(1, &id);
}
} // namespace GraphicLib::OpenGLImpl
