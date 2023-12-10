#pragma once

#include "GraphicLib/DLL_API.h"

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
    void Delete();

private:
    unsigned int _id{};
};
} // namespace GraphicLib
