#include "OpenGLImpl/VertexBufferOpsImpl.h"

#include "OpenGLImpl/glad.h"

namespace GraphicLib {
namespace OpenGLImpl {
void VertexBufferOpsImpl::InitialiseVertexBufferData(unsigned int& id) {
    glGenBuffers(1, &id);
}

void VertexBufferOpsImpl::Bind(unsigned int id) {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferOpsImpl::Unbind(unsigned int) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferOpsImpl::SendDataToGPU(unsigned int id, const StackArraySpan<unsigned int>& attributes, const StackArraySpan<float>& data) {
    Bind(id);

    const auto sizeOfArrayType{sizeof(StackArraySpan<float>::ArrayType)};

    glBufferData(GL_ARRAY_BUFFER, data.Count() * sizeOfArrayType, data.Data(), GL_STATIC_DRAW);

    unsigned int attributesSum{};
    for (unsigned int i{}; i < attributes.Count(); ++i) {
        const unsigned int attribute{attributes[i]};
        glVertexAttribPointer(i, static_cast<int>(attribute), GL_FLOAT, GL_FALSE, sizeOfArrayType, reinterpret_cast<void*>(attributesSum * sizeOfArrayType));
        glEnableVertexAttribArray(i);
        attributesSum += attribute;
    }
}
} // namespace OpenGLImpl
} // namespace GraphicLib
