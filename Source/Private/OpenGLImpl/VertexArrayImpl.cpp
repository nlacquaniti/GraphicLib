#include "OpenGLImpl/VertexArrayImpl.h"

#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
void VertexArrayImpl::Initialise(unsigned int& id) {
    glGenBuffers(1, &id);
}

void VertexArrayImpl::Bind(unsigned int id) {
    glBindVertexArray(id);
}

void VertexArrayImpl::Unbind(unsigned int) {
    glBindVertexArray(0);
}
} // namespace OpenGLImpl
} // namespace GraphicLib
