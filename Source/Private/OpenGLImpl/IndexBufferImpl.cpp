#include "OpenGLImpl/IndexBufferImpl.h"
#include "GraphicLib/IndexBuffer.h"

#include <glad/glad.h>

namespace GraphicLib::OpenGLImpl {
void IndexBufferImpl::Initialise(unsigned int& id) const {
    glGenBuffers(1, &id);
}

void IndexBufferImpl::Bind(unsigned int id) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBufferImpl::Unbind(unsigned int) const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBufferImpl::Set(unsigned int id, const std::vector<IndexBufferDataElement>& data) const {
    Bind(id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<long long>(data.size() * sizeof(IndexBufferDataElement)), data.data(), GL_STATIC_DRAW);
}

void IndexBufferImpl::Delete(unsigned int& id) const {
    Bind(id);
    glDeleteBuffers(1, &id);
}

} // namespace GraphicLib::OpenGLImpl
