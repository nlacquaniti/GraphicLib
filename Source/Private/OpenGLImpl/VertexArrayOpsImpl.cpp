#include "OpenGLImpl/VertexArrayOpsImpl.h"

#include "VertexBufferOpsImpl.h"
#include "IndexBufferOpsImpl.h"
#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
void VertexArrayOpsImpl::InitialiseVertexArrayData(unsigned int& id) {
    glGenBuffers(1, &id);
}

void VertexArrayOpsImpl::Bind(unsigned int id, unsigned int vertexBufferId, unsigned int indexBufferId) {
    glBindVertexArray(id);
    OpenGLImpl::VertexBufferOpsImpl::Bind(vertexBufferId);
    OpenGLImpl::IndexBufferOpsImpl::Bind(indexBufferId);
}

void VertexArrayOpsImpl::Unbind(unsigned int, unsigned int vertexBufferId, unsigned int indexBufferId) {
    glBindVertexArray(0);
    OpenGLImpl::VertexBufferOpsImpl::Unbind(vertexBufferId);
    OpenGLImpl::IndexBufferOpsImpl::Unbind(indexBufferId);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
