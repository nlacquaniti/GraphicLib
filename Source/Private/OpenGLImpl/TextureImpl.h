#pragma once

#include "GraphicLib/Texture.h"

namespace GraphicLib::OpenGLImpl {
class TextureImpl {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id, ETextureType type);
    static void Unbind(unsigned int id, ETextureType type);
    static void ActivateUnit(unsigned int id, ETextureType type, unsigned int slot);
    static void Set(unsigned int id, const TextureData& textureData, unsigned char* pixelData);
    static void Delete(unsigned int& id, ETextureType type);

private:
    static unsigned int _maxTextureSlots;
};
} // namespace GraphicLib::OpenGLImpl
