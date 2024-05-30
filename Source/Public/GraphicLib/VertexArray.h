#pragma once

#include "DLL_API.h"
#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/VertexBuffer.h"

namespace GraphicLib {
class DLL_API VertexArray {
public:
    VertexArray() noexcept;
    VertexArray(VertexArray&&) = delete;
    VertexArray& operator=(VertexArray&&) = delete;
    VertexArray(const VertexArray&) = delete;
    VertexArray& operator=(const VertexArray&) = delete;
    ~VertexArray() noexcept;
    void Bind();
    void Unbind();
    void Draw();
    void Delete();
    [[nodiscard]] const VertexBuffer& GetVertexBuffer() const;
    VertexBuffer& GetVertexBuffer();
    [[nodiscard]] const IndexBuffer& GetIndexBuffer() const;
    IndexBuffer& GetIndexBuffer();

private:
    VertexBuffer _vertexBuffer;
    IndexBuffer _indexBuffer;
    unsigned int _id{};
};
} // namespace GraphicLib
