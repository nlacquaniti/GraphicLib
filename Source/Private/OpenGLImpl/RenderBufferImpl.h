#pragma once

namespace GraphicLib::Internal {
#ifndef MOCK_OPENGL_IMPL
void InitialiseRenderBuffer(unsigned int* id);
void BindRenderBuffer(unsigned int id);
void UnbindRenderBuffer();
void SetRenderBuffer(unsigned int format, int width, int height);
void DeleteRenderBuffer(unsigned int* id);
#else
inline void InitialiseRenderBuffer(unsigned int* id) {
}
inline void BindRenderBuffer(unsigned int id) {
}
inline void UnbindRenderBuffer() {
}
inline void SetRenderBuffer(unsigned int format, int width, int height) {
}
inline void DeleteRenderBuffer(unsigned int* id) {
}
#endif
} // namespace GraphicLib::Internal
