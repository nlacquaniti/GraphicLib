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
void VertexArray::Initialise() {
    VertexArrayImpl::Initialise(_id);
    _vertexBuffer.Initialise();
    _indexBuffer.Initialise();
}

void VertexArray::Bind() {
    VertexArrayImpl::Bind(_id);
    _vertexBuffer.Bind();
    _indexBuffer.Bind();
}

void VertexArray::Unbind() {
    VertexArrayImpl::Unbind(_id);
    _vertexBuffer.Unbind();
    _indexBuffer.Unbind();
}

void VertexArray::Draw() {
    Bind();
    VertexArrayImpl::Draw(_id, _indexBuffer.Get().Size() * 3);
}

const VertexBuffer& VertexArray::GetVertexBuffer() const {
    return _vertexBuffer;
}

VertexBuffer& VertexArray::GetVertexBuffer() {
    return _vertexBuffer;
}

const IndexBuffer& VertexArray::GetIndexBuffer() const {
    return _indexBuffer;
}

IndexBuffer& VertexArray::GetIndexBuffer() {
    return _indexBuffer;
}
} // namespace GraphicLib
