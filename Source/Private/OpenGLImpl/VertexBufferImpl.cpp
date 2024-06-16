#include "OpenGLImpl/VertexBufferImpl.h"

#ifndef MOCK_OPENGL_IMPL
#include <glad/glad.h>

void GL_Internal_InitialiseVertexBuffer(GL_Internal_Id* id) {
    glGenBuffers(1, id);
}

void GL_Internal_BindVertexBuffer(GL_Internal_Id id) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void GL_Internal_UnbindVertexBuffer() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GL_Internal_SetVertexBuffer(const float* vertexData,
    size_t vertexDataSize,
    const int* vertexAttributes,
    size_t vertexAttributesSize) {
    glBufferData(GL_ARRAY_BUFFER,
        static_cast<long long>(vertexDataSize * sizeof(float)),
        vertexData,
        GL_STATIC_DRAW);

    int numberOfAttributes = 0;
    for (size_t i = 0; i < vertexAttributesSize; ++i) {
        numberOfAttributes += vertexAttributes[i];
    }

    int attributesSum = 0;
    for (unsigned int i{}; i < vertexAttributesSize; ++i) {
        const int attribute = vertexAttributes[i];

        glVertexAttribPointer(i,
            attribute,
            GL_FLOAT,
            GL_FALSE,
            numberOfAttributes * static_cast<int>(sizeof(float)),
            reinterpret_cast<void*>(
                static_cast<size_t>(attributesSum) * sizeof(float)));

        glEnableVertexAttribArray(i);
        attributesSum += attribute;
    }
}

void GL_Internal_DeleteVertexBuffer(unsigned int* id) {
    glDeleteBuffers(1, id);
}
#endif