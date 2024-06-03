#pragma once

namespace GraphicLib {
class Texture;
class RenderBuffer;
namespace OpenGLImpl {
class FrameBufferImpl {
public:
    void Initialise(unsigned int& id) const;
    void Bind(unsigned int id) const;
    void Unbind(unsigned int id) const;
    void Set(unsigned int id, const Texture& frameBufferTexture, const RenderBuffer& renderBuffer) const;
    void Delete(unsigned int& id) const;
};
} // namespace OpenGLImpl
} // namespace GraphicLib
