#include "OpenGLImpl/IndexBufferOpsImpl.h"

#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
void IndexBufferOpsImpl::InitialiseIndexBufferData(unsigned int& id) {
    glGenBuffers(1, &id);
}

void IndexBufferOpsImpl::Bind(unsigned int id) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBufferOpsImpl::Unbind(unsigned int) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferOpsImpl::SetData(unsigned int id, const StackArraySpan<unsigned int>& data) {
    Bind(id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.Count() * sizeof(StackArraySpan<unsigned int>::ArrayType), data.Data(), GL_STATIC_DRAW);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
