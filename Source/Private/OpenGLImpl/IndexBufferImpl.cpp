#include "OpenGLImpl/IndexBufferImpl.h"

#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
IndexBufferImpl::IndexBufferImpl() {
    glGenBuffers(1, &_id);
}

unsigned int IndexBufferImpl::_getID() const {
    return _id;
}

void IndexBufferImpl::_bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void IndexBufferImpl::_unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferImpl::_setData(const unsigned int* const dataArray, unsigned int dataArrayCount) const {
    _bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataArrayCount * sizeof(unsigned int), dataArray, GL_STATIC_DRAW);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
