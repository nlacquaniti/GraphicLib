#include "GraphicLib/IndexBuffer.h"

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/IndexBufferImpl.h"
using IndexBufferImpl = GraphicLib::OpenGLImpl::IndexBufferImpl;
#else
#error "No IndexBufferImpl has been detected."
#endif

namespace GraphicLib {
IndexBuffer* IndexBuffer::Create() {
    return new IndexBufferImpl();
}

unsigned int IndexBuffer::GetID() const {
    return _getID();
}

void IndexBuffer::Bind() const {
    _bind();
}

void IndexBuffer::Unbind() const {
    _unbind();
}

void IndexBuffer::SetData(const unsigned int* const dataArray, unsigned int dataArrayCount) {
    _setData(dataArray, dataArrayCount);
}
} // namespace GraphicLib
