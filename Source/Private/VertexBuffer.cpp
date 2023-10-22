#include "GraphicLib/VertexBuffer.h"

#include "InternalLogger.h"

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/VertexBufferImpl.h"
using VertexBufferImpl = GraphicLib::OpenGLImpl::VertexBufferImpl;
#else
#error "No VertexBufferImpl has been detected."
#endif

namespace GraphicLib {
VertexBuffer::VertexBuffer() {
    VertexBufferImpl::Initialise(_id);
}

void VertexBuffer::Bind() {
    VertexBufferImpl::Bind(_id);
}

void VertexBuffer::Unbind() {
    VertexBufferImpl::Unbind(_id);
}

void VertexBuffer::Set(const Span<float>& vertexData, const Span<int>& vertexAttributes) {
    _vertexData.SetData(vertexData);
    _vertexAttributes.SetData(vertexAttributes);
    VertexBufferImpl::Set(_id, vertexData, vertexAttributes);
}

Span<float> VertexBuffer::GetVertexData() const {
    return {_vertexData.Data(), _vertexData.Size()};
}

Span<int> VertexBuffer::GetVertexAttributes() const {
    return {_vertexAttributes.Data(), _vertexAttributes.Size()};
}
} // namespace GraphicLib
