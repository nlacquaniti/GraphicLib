#include "GraphicLib/VertexBuffer.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
VertexBuffer::~VertexBuffer() {
    Delete();
}

void VertexBuffer::Initialise() {
    GraphicAPI::Get().GetVertexBufferImpl().Initialise(_id);
}

void VertexBuffer::Bind() {
    GraphicAPI::Get().GetVertexBufferImpl().Bind(_id);
}

void VertexBuffer::Unbind() {
    GraphicAPI::Get().GetVertexBufferImpl().Unbind(_id);
}

void VertexBuffer::Set(const Span<float>& vertexData, const Span<int>& vertexAttributes) {
    _vertexData.SetData(vertexData);
    _vertexAttributes.SetData(vertexAttributes);
    Bind();
    GraphicAPI::Get().GetVertexBufferImpl().Set(_id, vertexData, vertexAttributes);
}

void VertexBuffer::Delete() {
    GraphicAPI::Get().GetVertexBufferImpl().Delete(_id);
}

Span<float> VertexBuffer::GetVertexData() const {
    return {_vertexData.Data(), _vertexData.Size()};
}

Span<int> VertexBuffer::GetVertexAttributes() const {
    return {_vertexAttributes.Data(), _vertexAttributes.Size()};
}
} // namespace GraphicLib
