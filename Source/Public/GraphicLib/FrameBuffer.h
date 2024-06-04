#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/RenderBuffer.h"
#include "GraphicLib/Texture.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"

namespace GraphicLib {
class DLL_API FrameBuffer {
public:
    FrameBuffer() noexcept = default;
    FrameBuffer(FrameBuffer&&) noexcept = default;
    FrameBuffer& operator=(FrameBuffer&&) noexcept = default;
    FrameBuffer(const FrameBuffer&) = delete;
    FrameBuffer& operator=(const FrameBuffer&) = delete;
    ~FrameBuffer() noexcept;
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set();
    [[nodiscard]] const Texture& GetTexture() const;
    Texture& GetTexture();
    [[nodiscard]] const RenderBuffer& GetRenderBuffer() const;
    RenderBuffer& GetRenderBuffer();

private:
    RenderBuffer _renderBuffer;
    Texture _texture;
    UniqueIdentifier _id;
};
} // namespace GraphicLib
