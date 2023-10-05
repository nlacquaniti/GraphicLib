#include "GraphicLib/VertexBuffer.h"

#include "InternalLogger.h"

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/VertexBufferOpsImpl.h"
using VertexBufferOpsImpl = GraphicLib::OpenGLImpl::VertexBufferOpsImpl;
#else
#error "No VertexBufferImpl has been detected."
#endif

namespace GraphicLib {
void VertexBufferOps::_initialiseVertexBufferData(unsigned int& id) {
    VertexBufferOpsImpl::InitialiseVertexBufferData(id);
}

void VertexBufferOps::_bind(unsigned int id) {
    VertexBufferOpsImpl::Bind(id);
}

void VertexBufferOps::_unbind(unsigned int id) {
    VertexBufferOpsImpl::Unbind(id);
}

void VertexBufferOps::_sendBufferToGPU(unsigned int id, const StackArraySpan<unsigned int>& attributes, const StackArraySpan<float>& data) {
    VertexBufferOpsImpl::SendDataToGPU(id, attributes, data);
}
} // namespace GraphicLib
