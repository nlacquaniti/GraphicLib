#include "OpenGLImpl/VertexArrayImpl.h"

#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/VertexBuffer.h"
#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
VertexArrayImpl::VertexArrayImpl() {
    glGenBuffers(1, &_id);
}

unsigned int VertexArrayImpl::_getID() const {
    return _id;
}

void VertexArrayImpl::_bind() const {
    glBindVertexArray(_id);
    GetVertexBuffer().Bind();
    GetIndexBuffer().Bind();
}

void VertexArrayImpl::_unbind() const {
    glBindVertexArray(0);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
