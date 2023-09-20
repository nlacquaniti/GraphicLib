#include "GraphicLib/VertexBuffer.h"

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/VertexBufferImpl.h"
using VertexBufferImpl = GraphicLib::OpenGLImpl::VertexBufferImpl;
#else
#error "No VertexBufferImpl has been detected."
#endif

namespace GraphicLib {
VertexBuffer* VertexBuffer::Create() {
    return new VertexBufferImpl();
}

unsigned int VertexBuffer::GetID() const {
    return _getID();
}

void VertexBuffer::Bind() const {
    _bind();
}

void VertexBuffer::Unbind() const {
    _unbind();
}

void VertexBuffer::SetData(const float* const vertexDataArray, unsigned int vertexDataArrayCount) const {
    _setData(vertexDataArray, vertexDataArrayCount);
}
} // namespace GraphicLib
