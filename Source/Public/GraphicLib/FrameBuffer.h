#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Texture.h"
#include "GraphicLib/RenderBuffer.h"

namespace GraphicLib {
class DLL_API FrameBuffer final {
public:
    FrameBuffer() = default;
    ~FrameBuffer();
    FrameBuffer(const FrameBuffer&) = default;
    FrameBuffer& operator=(const FrameBuffer&) = default;
    void Initialise();
    void Bind();
    void Unbind();
    void Set();
    void Delete();
    const Texture& GetTexture() const;
    Texture& GetTexture();
    const RenderBuffer& GetRenderBuffer() const;
    RenderBuffer& GetRenderBuffer();

private:
    unsigned int _id{};
    Texture _texture{};
    RenderBuffer _renderBuffer{};
};
} // namespace GraphicLib
