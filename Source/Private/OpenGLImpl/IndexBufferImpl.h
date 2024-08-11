#pragma once

namespace GraphicLib::Internal {
#ifndef MOCK_OPENGL_IMPL
void InitialiseIndexBuffer(unsigned int* id);
void BindIndexBuffer(unsigned int id);
void UnbindIndexBuffer();
void SetIndexBuffer(const unsigned int* indices, size_t indicesCount);
void DeleteIndexBuffer(unsigned int* id);
#else
inline void InitialiseIndexBuffer(unsigned int*) {};
inline void BindIndexBuffer(unsigned int) {};
inline void UnbindIndexBuffer() {};
inline void SetIndexBuffer(const unsigned int*, size_t) {};
inline void DeleteIndexBuffer(unsigned int*) {};
#endif
}