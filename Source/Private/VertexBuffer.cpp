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

void VertexBuffer::Set(std::vector<float>&& vertexData, std::vector<int>&& vertexAttributes) {
    _vertexData = std::move(vertexData);
    _vertexAttributes = std::move(vertexAttributes);
    Bind();
    GraphicAPI::Get().GetVertexBufferImpl().Set(_id, _vertexData, _vertexAttributes);
}

void VertexBuffer::Delete() {
    GraphicAPI::Get().GetVertexBufferImpl().Delete(_id);
}

const std::vector<float>& VertexBuffer::GetVertexData() const {
    return _vertexData;
}

const std::vector<int>& VertexBuffer::GetVertexAttributes() const {
    return _vertexAttributes;
}
} // namespace GraphicLib
