#pragma once

#include "GraphicLib/DLL_API.h"
#include "GraphicLib/Utilities/UniqueIdentifier.h"

namespace GraphicLib {
enum class ERenderBufferFormat : unsigned char {
    NONE,
    DEPTH16,
    DEPTH24,
    DEPTH32,
    STENCIL8,
    DEPTH24_STENCIL8,
};

struct RenderBufferData {
    ERenderBufferFormat Format{};
    int Width{};
    int Height{};
};

class DLL_API RenderBuffer {
public:
    RenderBuffer() noexcept = default;
    RenderBuffer(RenderBuffer&&) noexcept = default;
    RenderBuffer& operator=(RenderBuffer&&) noexcept = default;
    RenderBuffer(const RenderBuffer&) = delete;
    RenderBuffer& operator=(const RenderBuffer&) = delete;
    ~RenderBuffer() noexcept;
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set(const RenderBufferData& data);
    [[nodiscard]] unsigned int GetID() const;
    [[nodiscard]] const RenderBufferData& GetData() const;

private:
    RenderBufferData _data{};
    UniqueIdentifier _id;
};
} // namespace GraphicLib
