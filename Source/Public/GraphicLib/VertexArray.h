#pragma once

#include "DLL_API.h"
#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/VertexBuffer.h"

namespace GraphicLib {
class DLL_API VertexArray final {
public:
    void Initialise();
    void Bind();
    void Unbind();
    void Draw();
    const VertexBuffer& GetVertexBuffer() const;
    VertexBuffer& GetVertexBuffer();
    const IndexBuffer& GetIndexBuffer() const;
    IndexBuffer& GetIndexBuffer();

private:
    VertexBuffer _vertexBuffer{};
    IndexBuffer _indexBuffer{};
    unsigned int _id{};
};
} // namespace GraphicLib
