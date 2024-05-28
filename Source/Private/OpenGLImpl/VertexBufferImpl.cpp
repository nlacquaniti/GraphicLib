#include "OpenGLImpl/VertexBufferImpl.h"

#include <glad/glad.h>

namespace GraphicLib::OpenGLImpl {
void VertexBufferImpl::Initialise(unsigned int& id) {
    glGenBuffers(1, &id);
}

void VertexBufferImpl::Bind(unsigned int id) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferImpl::Unbind(unsigned int /*unused*/) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferImpl::Set(unsigned int /*unused*/, const std::vector<float>& data, const std::vector<VertexAttribute>& attributes) {
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(data.size() * sizeof(float)), data.data(), GL_STATIC_DRAW);

    int numberOfAttributes{};
    for (unsigned int i{}; i < attributes.size(); ++i) {
        numberOfAttributes += attributes[i].Size;
    }

    int attributesSum{};
    for (unsigned int i{}; i < attributes.size(); ++i) {
        const int attribute{attributes[i].Size};
        constexpr unsigned long long sizeOfFloat{sizeof(float)};
        glVertexAttribPointer(i, attribute, GL_FLOAT, GL_FALSE, numberOfAttributes * static_cast<int>(sizeOfFloat),
            reinterpret_cast<void*>(static_cast<unsigned long long>(attributesSum) * sizeOfFloat));
        glEnableVertexAttribArray(i);
        attributesSum += attribute;
    }
}

void VertexBufferImpl::Delete(unsigned int& id) {
    glDeleteBuffers(1, &id);
}
} // namespace GraphicLib::OpenGLImpl
