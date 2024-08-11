#ifndef MOCK_OPENGL_IMPL
#include "OpenGLImpl/VertexArrayImpl.h"

#include <glad/glad.h>

namespace GraphicLib::Internal {
void InitialiseVertexArray(unsigned int* id) {
    glGenVertexArrays(1, id);
}

void BindVertexArray(unsigned int id) {
    glBindVertexArray(id);
}

void UnbindVertexArray() {
    glBindVertexArray(0);
}

void DrawTrianglesVertexArray(int trianglesCount) {
    glDrawElements(GL_TRIANGLES, trianglesCount, GL_UNSIGNED_INT, nullptr);
}

void DrawVerticesVertexArray(int verticesCount) {
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

void DeleteVertexArray(unsigned int* id) {
    glDeleteVertexArrays(1, id);
}
} // namespace GraphicLib::Internal
#endif
