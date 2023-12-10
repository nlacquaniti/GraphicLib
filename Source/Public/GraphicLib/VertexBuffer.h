#pragma once

#include "DLL_API.h"
#include "GraphicLib/Utilities/Array.h"
#include "GraphicLib/Utilities/Span.h"

namespace GraphicLib {
class DLL_API VertexBuffer final {
public:
    VertexBuffer() = default;
    ~VertexBuffer();
    VertexBuffer(const VertexBuffer&) = default;
    VertexBuffer& operator=(const VertexBuffer&) = default;
    void Initialise();
    void Bind();
    void Unbind();
    void Set(const Span<float>& vertexData, const Span<int>& vertexAttributes);
    void Delete();
    Span<float> GetVertexData() const;
    Span<int> GetVertexAttributes() const;

private:
    Array<float> _vertexData{};
    Array<int> _vertexAttributes{};
    unsigned int _id{};
};
} // namespace GraphicLib
