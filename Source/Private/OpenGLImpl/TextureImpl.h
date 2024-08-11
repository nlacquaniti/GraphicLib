#pragma once

namespace GraphicLib::Internal {
struct TextureParameter {
    unsigned int Name;
    int Value;
};

struct TextureData {
    static constexpr size_t MAX_PARAMETERS_COUNT = 4;
    Internal::TextureParameter Parameters[MAX_PARAMETERS_COUNT];
    const void* PixelData;
    unsigned int Type;
    unsigned int TextureFormat;
    unsigned int DataType;
    int Format;
    int Width;
    int Height;
};

#ifndef MOCK_OPENGL_IMPL
void InitialiseTexture(unsigned int* id);
void BindTexture(unsigned int id, unsigned int type);
void UnbindTexture(unsigned int id, unsigned int type);
void SetTextureSlot(unsigned int slot);
void SetTexture(const Internal::TextureData& textureData);
int GetMaxTextureSlots();
void DeleteTexture(unsigned int* id);
#else
inline void InitialiseTexture(unsigned int* id) {
}
inline void BindTexture(unsigned int id, unsigned int type) {
}
inline void UnbindTexture(unsigned int id, unsigned int type) {
}
inline void SetTextureSlot(unsigned int slot) {
}
inline void SetTexture(const Internal::TextureData& textureData) {
}
inline int GetMaxTextureSlots() {
    return 0;
}
void DeleteTexture(unsigned int* id) {
}
#endif
} // namespace GraphicLib::Internal
