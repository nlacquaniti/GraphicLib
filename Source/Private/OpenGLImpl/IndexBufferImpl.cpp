#include "OpenGLImpl/IndexBufferImpl.h"

#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
void IndexBufferImpl::Initialise(unsigned int& id) {
    glGenBuffers(1, &id);
}

void IndexBufferImpl::Bind(unsigned int id) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBufferImpl::Unbind(unsigned int) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferImpl::Set(unsigned int id, const Span<IndexBufferDataElement>& data) {
    Bind(id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long>(data.SizeBytes()), data.Data(), GL_STATIC_DRAW);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
