#include "OpenGLImpl/VertexBufferImpl.h"
#include "GraphicLib/VertexBuffer.h"

#include <glad/glad.h>

namespace GraphicLib::OpenGLImpl {
void VertexBufferImpl::Initialise(unsigned int& id) const {
    // int maxVertexAttribs;
    // glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);
    // std::cout << "GL_MAX_VERTEX_ATTRIBS" << maxVertexAttribs << std::endl;
    glGenBuffers(1, &id);
}

void VertexBufferImpl::Bind(unsigned int id) const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferImpl::Unbind(unsigned int /*unused*/) const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferImpl::Set(unsigned int /*unused*/, const std::vector<float>& vertexData, const std::span<const VertexAttribute>& vertexAttributes) const {
    glBufferData(GL_ARRAY_BUFFER, static_cast<long long>(vertexData.size() * sizeof(float)), vertexData.data(), GL_STATIC_DRAW);
    int numberOfAttributes{};
    for (const VertexAttribute& vertexAttribute : vertexAttributes) {
        numberOfAttributes += vertexAttribute.Count;
    }

    int attributesSum{};
    for (unsigned int i{}; i < vertexAttributes.size(); ++i) {
        const int attribute{vertexAttributes[i].Count};
        constexpr unsigned long long sizeOfFloat{sizeof(float)};
        glVertexAttribPointer(i, attribute, GL_FLOAT, GL_FALSE, numberOfAttributes * static_cast<int>(sizeOfFloat),
            reinterpret_cast<void*>(static_cast<unsigned long long>(attributesSum) * sizeOfFloat));
        glEnableVertexAttribArray(i);
        attributesSum += attribute;
    }
}

void VertexBufferImpl::Delete(unsigned int& id) const {
    glDeleteBuffers(1, &id);
}
} // namespace GraphicLib::OpenGLImpl
