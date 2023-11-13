#include "GraphicLib/IndexBuffer.h"

#include "InternalLogger.h"

#ifdef OPENGL_IMPL
#include "OpenGLImpl/IndexBufferImpl.h"
using IndexBufferImpl = GraphicLib::OpenGLImpl::IndexBufferImpl;
#else
#error "No IndexBufferImpl has been detected."
#endif

namespace GraphicLib {
void IndexBuffer::Initialise() {
    IndexBufferImpl::Initialise(_id);
}

void IndexBuffer::Bind() {
    IndexBufferImpl::Bind(_id);
}

void IndexBuffer::Unbind() {
    IndexBufferImpl::Unbind(_id);
}

void IndexBuffer::Set(const Span<IndexBufferDataElement>& indices) {
    _indices.SetData(indices);
    IndexBufferImpl::Set(_id, indices);
}

Span<IndexBufferDataElement> IndexBuffer::Get() const {
    return {_indices.Data(), _indices.Size()};
}

} // namespace GraphicLib
