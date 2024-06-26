#pragma once

#include "GraphicLib/Texture.h"

namespace GraphicLib::OpenGLImpl {
class TextureImpl {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id, ETextureType type) const;
    void Unbind(unsigned int id, ETextureType type) const;
    void SetTextureSlot(unsigned int id, ETextureType type, unsigned int slot) const;
    void Set(unsigned int id, const TextureData& textureData) const;
    void Delete(unsigned int& id, ETextureType type) const;

private:
    static unsigned int _maxTextureSlots;
};
} // namespace GraphicLib::OpenGLImpl
