#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/RenderBuffer.h"
#include "GraphicLib/Texture.h"

namespace GraphicLib {
class DLL_API FrameBuffer {
public:
    FrameBuffer() = default;
    FrameBuffer(FrameBuffer&&) = default;
    FrameBuffer& operator=(FrameBuffer&&) = default;
    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer& operator=(const FrameBuffer&) = delete;
    ~FrameBuffer();
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set();
    void Delete();
    [[nodiscard]] const Texture& GetTexture() const;
    Texture& GetTexture();
    [[nodiscard]] const RenderBuffer& GetRenderBuffer() const;
    RenderBuffer& GetRenderBuffer();

private:
    RenderBuffer _renderBuffer;
    Texture _texture;
    unsigned int _id{};
};
} // namespace GraphicLib
