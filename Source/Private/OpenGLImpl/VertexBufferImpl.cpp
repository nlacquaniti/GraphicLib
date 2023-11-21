#include "OpenGLImpl/VertexBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib {
namespace OpenGLImpl {
void VertexBufferImpl::Initialise(unsigned int& id) const {
    glGenBuffers(1, &id);
}

void VertexBufferImpl::Bind(unsigned int id) const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferImpl::Unbind(unsigned int) const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferImpl::Set(unsigned int id, const Span<float>& data, const Span<int>& attributes) const {
    Bind(id);

    glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(data.SizeBytes()), data.Data(), GL_STATIC_DRAW);

    int numberOfAttributes{};
    for (unsigned int i{}; i < attributes.Size(); ++i) {
        numberOfAttributes += attributes[i];
    }

    int attributesSum{};
    for (unsigned int i{}; i < attributes.Size(); ++i) {
        const int attribute{attributes[i]};
        constexpr unsigned long long sizeOfFloat{sizeof(float)};
        glVertexAttribPointer(i, attribute, GL_FLOAT, GL_FALSE, numberOfAttributes * static_cast<int>(sizeOfFloat),
            reinterpret_cast<void*>(static_cast<unsigned long long>(attributesSum) * sizeOfFloat));
        glEnableVertexAttribArray(i);
        attributesSum += attribute;
    }
}
} // namespace OpenGLImpl
} // namespace GraphicLib
