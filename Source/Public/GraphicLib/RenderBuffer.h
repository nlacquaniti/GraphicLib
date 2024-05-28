#pragma once

#include "DLL_API.h"

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
    RenderBuffer() = default;
    RenderBuffer(RenderBuffer&&) = default;
    RenderBuffer& operator=(RenderBuffer&&) = default;
    RenderBuffer(const RenderBuffer&) = delete;
    RenderBuffer& operator=(const RenderBuffer&) = delete;
    ~RenderBuffer();
    void Initialise();
    void Bind() const;
    void Unbind() const;
    void Set(const RenderBufferData& data);
    void Delete();
    [[nodiscard]] unsigned int GetID() const;
    [[nodiscard]] const RenderBufferData& GetData() const;

private:
    RenderBufferData _data{};
    unsigned int _id{};
};
} // namespace GraphicLib
