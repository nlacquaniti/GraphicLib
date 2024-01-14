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
    ~RenderBuffer();
    RenderBuffer(const RenderBuffer&) = default;
    RenderBuffer& operator=(const RenderBuffer&) = default;
    void Initialise();
    void Bind();
    void Unbind();
    void Set(const RenderBufferData& data);
    void Delete();
    unsigned int GetID() const;
    const RenderBufferData& GetData() const;

private:
    unsigned int _id{};
    RenderBufferData _data;
};
} // namespace GraphicLib
