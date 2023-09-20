#include "OpenGLImpl/VertexBufferImpl.h"

#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
VertexBufferImpl::VertexBufferImpl() {
    glGenBuffers(1, &_id);
}

unsigned int VertexBufferImpl::_getID() const {
    return _id;
}

void VertexBufferImpl::_bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBufferImpl::_unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferImpl::_setData(const float* const vertexDataArray, unsigned int vertexDataArrayCount) const {
    _bind();

    glBufferData(GL_ARRAY_BUFFER, vertexDataArrayCount * sizeof(float), vertexDataArray, GL_STATIC_DRAW);

    // TODO: this should be dynamic, all the attributes should be decided at runtime
    // by the user.

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
