#include "OpenGLImpl/IndexBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib::OpenGLImpl {
void IndexBufferImpl::Initialise(unsigned int& id) const {
    glGenBuffers(1, &id);
}

void IndexBufferImpl::Bind(unsigned int id) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBufferImpl::Unbind(unsigned int /*unused*/) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferImpl::Set(unsigned int /*unused*/, const std::vector<unsigned int>& indicies) const {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long>(indicies.size() * sizeof(unsigned int)), indicies.data(), GL_STATIC_DRAW);
}

void IndexBufferImpl::Delete(unsigned int& id) const {
    glDeleteBuffers(1, &id);
}

} // namespace GraphicLib::OpenGLImpl
