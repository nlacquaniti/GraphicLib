#pragma once

#include "DLL_API.h"
#include "GraphicLib/Utilities/Array.h"
#include "GraphicLib/Utilities/Span.h"

namespace GraphicLib {
struct IndexBufferDataElement {
    unsigned int E1{};
    unsigned int E2{};
    unsigned int E3{};
};

class DLL_API IndexBuffer final {
public:
    IndexBuffer() = default;
    ~IndexBuffer();
    IndexBuffer(const IndexBuffer&) = default;
    IndexBuffer& operator=(const IndexBuffer&) = default;
    void Initialise();
    void Bind();
    void Unbind();
    void Set(const Span<IndexBufferDataElement>& indices);
    void Delete();
    Span<IndexBufferDataElement> Get() const;

private:
    Array<IndexBufferDataElement> _indices{};
    unsigned int _id{};
};
} // namespace GraphicLib
