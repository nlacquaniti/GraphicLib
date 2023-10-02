#include "GraphicLib/VertexArray.h"

#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/VertexBuffer.h"
#include <cassert>

#ifdef OPEN_GL_IMPL
#include "OpenGLImpl/VertexArrayOpsImpl.h"
using VertexArrayOpsImpl = GraphicLib::OpenGLImpl::VertexArrayOpsImpl;
#else
#error "No VertexArrayImpl has been detected."
#endif

namespace GraphicLib {
void VertexArrayOps::_initialiseVertexArrayData(unsigned int& id) {
    VertexArrayOpsImpl::InitialiseVertexArrayData(id);
}

void VertexArrayOps::_bind(unsigned int id, unsigned int vertexBufferId, unsigned int indexBufferId) {
    VertexArrayOpsImpl::Bind(id, vertexBufferId, indexBufferId);
}

void VertexArrayOps::_unbind(unsigned int id, unsigned int vertexBufferId, unsigned int indexBufferId) {
    VertexArrayOpsImpl::Unbind(id, vertexBufferId, indexBufferId);
}
} // namespace GraphicLib
