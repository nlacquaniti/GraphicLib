#pragma once

namespace GraphicLib {
class Texture;
class RenderBuffer;
namespace OpenGLImpl {
class FrameBufferImpl {
public:
    static void Initialise(unsigned int& id);
    static void Bind(unsigned int id);
    static void Unbind(unsigned int id);
    static void Set(unsigned int id, const Texture& frameBufferTexture, const RenderBuffer& renderBuffer);
    static void Delete(unsigned int& id);
};
} // namespace OpenGLImpl
} // namespace GraphicLib
