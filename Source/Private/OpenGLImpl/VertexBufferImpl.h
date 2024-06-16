#pragma once

typedef unsigned int GL_Internal_Id;

#ifndef MOCK_OPENGL_IMPL
void GL_Internal_InitialiseVertexBuffer(GL_Internal_Id* id);
void GL_Internal_BindVertexBuffer(GL_Internal_Id id);
void GL_Internal_UnbindVertexBuffer();
void GL_Internal_SetVertexBuffer(const float* vertexData,
    size_t vertexDataSize,
    const int* vertexAttributes,
    size_t vertexAttributesSize);
void GL_Internal_DeleteVertexBuffer(GL_Internal_Id* id);
#else
inline void GL_Internal_InitialiseVertexBuffer(GL_Internal_Id*) {};
inline void GL_Internal_BindVertexBuffer(GL_Internal_Id){};
inline void GL_Internal_UnbindVertexBuffer() {};
inline void
GL_Internal_SetVertexBuffer(const float*, size_t, const int*, size_t) {};
inline void GL_Internal_DeleteVertexBuffer(GL_Internal_Id*) {};
#endif
