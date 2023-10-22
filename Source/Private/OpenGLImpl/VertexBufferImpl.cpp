#include "OpenGLImpl/VertexBufferImpl.h"

#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
void VertexBufferImpl::Initialise(unsigned int& id) {
    glGenBuffers(1, &id);
}

void VertexBufferImpl::Bind(unsigned int id) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferImpl::Unbind(unsigned int) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferImpl::Set(unsigned int id, const Span<float>& data, const Span<int>& attributes) {
    Bind(id);

    glBufferData(GL_ARRAY_BUFFER, data.SizeBytes(), data.Data(), GL_STATIC_DRAW);

    int attributesSum{};
    for (unsigned int i{}; i < attributes.Size(); ++i) {
        const int attribute{attributes[i]};
        glVertexAttribPointer(i, attribute, GL_FLOAT, GL_FALSE, sizeof(float), reinterpret_cast<void*>(static_cast<unsigned int>(attributesSum) * sizeof(float)));
        glEnableVertexAttribArray(i);
        attributesSum += attribute;
    }
}
} // namespace OpenGLImpl
} // namespace GraphicLib
