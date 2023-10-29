#pragma once

#include "GraphicLib/Texture.h"

namespace GraphicLib {
namespace OpenGLImpl {
class TextureImpl final {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id, TextureType type);
    static void Unbind(unsigned int id, TextureType type);
    static void Draw(unsigned int id, TextureType type, unsigned char slot);
    static void Set(unsigned int id, const TextureData& textureData);
private:
    static int _maxTextureSlots;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
