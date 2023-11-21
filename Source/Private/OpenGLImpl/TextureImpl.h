#pragma once

#include "GraphicLib/Texture.h"

namespace GraphicLib {
namespace OpenGLImpl {
class TextureImpl final {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id, TextureType type) const;
    void Unbind(unsigned int id, TextureType type) const ;
    void Draw(unsigned int id, TextureType type, unsigned char slot) const;
    void Set(unsigned int id, const TextureData& textureData) const;
private:
    static int _maxTextureSlots;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
