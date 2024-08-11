#pragma once

namespace GraphicLib::Internal {
#ifndef MOCK_OPENGL_IMPL
void InitialiseVertexArray(unsigned int* id);
void BindVertexArray(unsigned int id);
void UnbindVertexArray();
void DrawTrianglesVertexArray(int trianglesCount);
void DrawVerticesVertexArray(int verticesCount);
void DeleteVertexArray(unsigned int* id);
#else
inline void InitialiseVertexArray(unsigned int*) {
}
inline void BindVertexArray(unsigned int) {
}
inline void UnbindVertexArray() {
}
inline void DrawTrianglesVertexArray(int) {
}
inline void DrawVerticesVertexArray(int) {
}
inline void DeleteVertexArray(unsigned int*) {
}
#endif
} // namespace GraphicLib::Internal
