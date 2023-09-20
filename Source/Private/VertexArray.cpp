#include "GraphicLib/VertexArray.h"

#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/VertexBuffer.h"
#include <cassert>

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/VertexArrayImpl.h"
using VertexArrayImpl = GraphicLib::OpenGLImpl::VertexArrayImpl;
#else
#error "No VertexArrayImpl has been detected."
#endif

namespace GraphicLib {
VertexArray* VertexArray::Create(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer) {
    _vertexBuffer = vertexBuffer;
    assert(_vertexBuffer != nullptr);
    _indexBuffer = indexBuffer;
    assert(_indexBuffer != nullptr);
    return new VertexArrayImpl();
}

unsigned int VertexArray::GetID() const {
    return _getID();
}

VertexBuffer& VertexArray::GetVertexBuffer() {
    return *_vertexBuffer;
}

const VertexBuffer& VertexArray::GetVertexBuffer() const {
    return *_vertexBuffer;
}

IndexBuffer& VertexArray::GetIndexBuffer() {
    return *_indexBuffer;
}

const IndexBuffer& VertexArray::GetIndexBuffer() const {
    return *_indexBuffer;
}

void VertexArray::Bind() const {
    _bind();
}

void VertexArray::Unbind() const {
    _unbind();
}
} // namespace GraphicLib
