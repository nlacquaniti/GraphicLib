#include "GraphicLib/IndexBuffer.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/APIImpl.h"
using GraphicAPI = GraphicLib::OpenGLImpl::APIImpl;
#else
#error "No GraphicAPI has been detected."
#endif

namespace GraphicLib {
IndexBuffer::~IndexBuffer() {
    Delete();
}

void IndexBuffer::Initialise() {
    GraphicAPI::Get().GetIndexBufferImpl().Initialise(_id);
}

void IndexBuffer::Bind() const {
    GraphicAPI::Get().GetIndexBufferImpl().Bind(_id);
}

void IndexBuffer::Unbind() const {
    GraphicAPI::Get().GetIndexBufferImpl().Unbind(_id);
}

void IndexBuffer::Set(std::vector<int>&& indices) {
    _indices = std::move(indices);
    Bind();
    GraphicAPI::Get().GetIndexBufferImpl().Set(_id, _indices);
}

void IndexBuffer::Delete() {
    GraphicAPI::Get().GetIndexBufferImpl().Delete(_id);
}

const std::vector<int>& IndexBuffer::Get() const {
    return _indices;
}
} // namespace GraphicLib
