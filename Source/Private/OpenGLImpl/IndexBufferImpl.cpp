#include "OpenGLImpl/IndexBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib {
namespace OpenGLImpl {
void IndexBufferImpl::Initialise(unsigned int& id) const {
    glGenBuffers(1, &id);
}

void IndexBufferImpl::Bind(unsigned int id) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBufferImpl::Unbind(unsigned int) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferImpl::Set(unsigned int id, const Span<IndexBufferDataElement>& data) const {
    Bind(id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long>(data.SizeBytes()), data.Data(), GL_STATIC_DRAW);
}

void IndexBufferImpl::Delete(unsigned int& id) const {
    Bind(id);
    glDeleteBuffers(1, &id);
}

} // namespace OpenGLImpl
} // namespace GraphicLib
