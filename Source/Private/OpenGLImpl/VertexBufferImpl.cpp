#ifndef MOCK_OPENGL_IMPL
#include "OpenGLImpl/VertexBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib::Internal {
void InitialiseVertexBuffer(unsigned int* id) {
    glGenBuffers(1, id);
}

void BindVertexBuffer(unsigned int id) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void UnbindVertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SetVertexBuffer(const float* vertexData,
    size_t vertexDataSize,
    const int* vertexAttributes,
    size_t vertexAttributesSize) {
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(vertexDataSize * sizeof(float)),
        vertexData, GL_STATIC_DRAW);

    int numberOfAttributes = 0;
    for (size_t i = 0; i < vertexAttributesSize; ++i) {
        numberOfAttributes += vertexAttributes[i];
    }

    int attributesSum = 0;
    for (unsigned int i{}; i < vertexAttributesSize; ++i) {
        const int attribute = vertexAttributes[i];

        glVertexAttribPointer(i, attribute, GL_FLOAT, GL_FALSE,
            numberOfAttributes * static_cast<int>(sizeof(float)),
            reinterpret_cast<void*>(static_cast<size_t>(attributesSum) * sizeof(float)));

        glEnableVertexAttribArray(i);
        attributesSum += attribute;
    }
}

void DeleteVertexBuffer(unsigned int* id) {
    glDeleteBuffers(1, id);
}
} // namespace GraphicLib::Internal
#endif