#pragma once

namespace GraphicLib::Internal {
#ifndef MOCK_OPENGL_IMPL
void InitialiseFrameBuffer(unsigned int* id);
void BindFrameBuffer(unsigned int id);
void UnbindFrameBuffer();
bool SetFrameBuffer(unsigned int textureId,
    unsigned int frameBufferAttachement,
    unsigned int textureType,
    unsigned int renderBufferId,
    unsigned int renderBufferAttachment);
void DeleteFrameBuffer(unsigned int* id);
#else
inline void InitialiseFrameBuffer(unsigned int* id) {
}
inline void BindFrameBuffer(unsigned int id) {
}
inline void UnbindFrameBuffer() {
}
inline bool SetFrameBuffer(unsigned int textureId,
    unsigned int frameBufferAttachement,
    unsigned int textureType,
    unsigned int renderBufferId,
    unsigned int renderBufferAttachment) {
    return true;
}
inline void DeleteFrameBuffer(unsigned int* id) {
}
#endif
} // namespace GraphicLib::Internal
