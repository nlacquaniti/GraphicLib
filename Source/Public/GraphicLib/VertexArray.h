#pragma once

#include "DLL_API.h"

namespace GraphicLib {
class VertexBuffer;
class IndexBuffer;
class DLL_API VertexArray {
public:
    VertexArray* Create(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer);
    virtual ~VertexArray() = default;
    VertexArray(const VertexArray& other) = delete;
    VertexArray& operator=(const VertexArray& other) = delete;
    unsigned int GetID() const;
    const VertexBuffer& GetVertexBuffer() const;
    VertexBuffer& GetVertexBuffer();
    const IndexBuffer& GetIndexBuffer() const;
    IndexBuffer& GetIndexBuffer();
    void Bind() const;
    void Unbind() const;

protected:
    VertexArray() = default;

private:
    virtual unsigned int _getID() const = 0;
    virtual void _bind() const = 0;
    virtual void _unbind() const = 0;
    VertexBuffer* _vertexBuffer{};
    IndexBuffer* _indexBuffer{};
};
} // namespace GraphicLib
