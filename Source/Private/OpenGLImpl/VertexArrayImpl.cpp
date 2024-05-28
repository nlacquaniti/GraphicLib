#include "OpenGLImpl/VertexArrayImpl.h"

#include <glad/glad.h>

namespace GraphicLib::OpenGLImpl {
void VertexArrayImpl::Initialise(unsigned int& id) {
    glGenVertexArrays(1, &id);
}

void VertexArrayImpl::Bind(unsigned int id) {
    glBindVertexArray(id);
}

void VertexArrayImpl::Unbind(unsigned int /*unused*/) {
    glBindVertexArray(0);
}

void VertexArrayImpl::DrawTriangles(unsigned int /*unused*/, int trianglesCount) {
    glDrawElements(GL_TRIANGLES, trianglesCount, GL_UNSIGNED_INT, nullptr);
}

void VertexArrayImpl::DrawVertices(unsigned int /*unused*/, int verticesCount) {
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void VertexArrayImpl::Delete(unsigned int& id) {
    glDeleteVertexArrays(1, &id);
}
} // namespace GraphicLib::OpenGLImpl
