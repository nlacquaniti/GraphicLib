#pragma once

namespace GraphicLib::Internal {
#ifndef MOCK_OPENGL_IMPL
void InitialiseVertexBuffer(unsigned int* id);
void BindVertexBuffer(unsigned int id);
void UnbindVertexBuffer();
void SetVertexBuffer(const float* vertexData,
    size_t vertexDataSize,
    const int* vertexAttributes,
    size_t vertexAttributesSize);
void DeleteVertexBuffer(unsigned int* id);
#else
inline void InitialiseVertexBuffer(unsigned int*) {
}
inline void BindVertexBuffer(unsigned int) {
}
inline void UnbindVertexBuffer() {
}
inline void SetVertexBuffer(const float*, size_t, const int*, size_t) {
}
inline void DeleteVertexBuffer(unsigned int*) {
}
#endif
} // namespace GraphicLib::Internal