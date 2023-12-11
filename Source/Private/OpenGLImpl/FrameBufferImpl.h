#pragma once

namespace GraphicLib {
struct TextureData;
namespace OpenGLImpl {
class FrameBufferImpl final {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void Set(unsigned int id, const TextureData& frameBufferTextureData);
    void Delete(unsigned int& id) const;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
