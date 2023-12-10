#include "GraphicLib/IndexBuffer.h"

#include "InternalLogger.h"

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

void IndexBuffer::Bind() {
    GraphicAPI::Get().GetIndexBufferImpl().Bind(_id);
}

void IndexBuffer::Unbind() {
    GraphicAPI::Get().GetIndexBufferImpl().Unbind(_id);
}

void IndexBuffer::Set(const Span<IndexBufferDataElement>& indices) {
    _indices.SetData(indices);
    Bind();
    GraphicAPI::Get().GetIndexBufferImpl().Set(_id, indices);
}

void IndexBuffer::Delete() {
    GraphicAPI::Get().GetIndexBufferImpl().Delete(_id);
}

Span<IndexBufferDataElement> IndexBuffer::Get() const {
    return {_indices.Data(), _indices.Size()};
}
} // namespace GraphicLib
