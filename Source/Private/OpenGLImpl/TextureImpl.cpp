#ifndef MOCK_OPENGL_IMPL
#include "OpenGLImpl/TextureImpl.h"

#include <glad/glad.h>

namespace GraphicLib::Internal {
void InitialiseTexture(unsigned int* id) {
    glGenTextures(1, id);
}

void BindTexture(unsigned int id, unsigned int type) {
    glBindTexture(type, id);
}

void UnbindTexture(unsigned int, unsigned int type) {
    glBindTexture(type, 0);
}

void SetTextureSlot(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
}

void SetTexture(const Internal::TextureData& textureData) {
    for (unsigned long long i{}; i < Internal::TextureData::MAX_PARAMETERS_COUNT; ++i) {
        const Internal::TextureParameter& param = textureData.Parameters[i];
        glTexParameteri(textureData.Type, param.Name, param.Value);
    }

    glTexImage2D(textureData.Type, 0, textureData.Format, textureData.Width,
        textureData.Height, 0, textureData.TextureFormat, textureData.DataType,
        textureData.PixelData);
    glGenerateMipmap(textureData.Type);
}

int GetMaxTextureSlots() {
    int maxTextureSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureSlots);
    return maxTextureSlots;
}

void DeleteTexture(unsigned int* id) {
    glDeleteTextures(1, id);
}
} // namespace GraphicLib::Internal
#endif
