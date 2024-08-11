#include "GraphicLib/GL_VertexArray.h"

#include "GraphicLib/Storage.h"

#include "OpenGLImpl/IndexBufferImpl.h"
#include "OpenGLImpl/VertexBufferImpl.h"
#include "OpenGLImpl/VertexArrayImpl.h"

#include <algorithm>

namespace GraphicLib {
namespace {
unsigned int CreateVertexBuffer(const GraphicLib::VertexBuffer& vertexBuffer) {
    std::array<int, GraphicLib::VertexBuffer::ATTRIBUTES_MAX_SIZE> openGLVertexAttributes;
    std::transform(vertexBuffer.VertexAttributes.cbegin(),
        vertexBuffer.VertexAttributes.cbegin() +
            static_cast<ptrdiff_t>(vertexBuffer.VertexAttributesCount),
        openGLVertexAttributes.begin(),
        [](const VertexAttribute& vertexAttribute) { return vertexAttribute.Count; });

    unsigned int openGLIndex;
    Internal::InitialiseVertexBuffer(&openGLIndex);
    Internal::BindVertexBuffer(openGLIndex);

    Internal::SetVertexBuffer(vertexBuffer.VertexData.data(),
        vertexBuffer.VertexData.size(), openGLVertexAttributes.data(),
        vertexBuffer.VertexAttributesCount);

    Internal::UnbindVertexBuffer();

    return openGLIndex;
}

unsigned int CreateIndexBuffer(const GraphicLib::IndexBuffer& indexBuffer) {
    unsigned int openGLId;
    Internal::InitialiseVertexBuffer(&openGLId);
    Internal::BindIndexBuffer(openGLId);
    Internal::SetIndexBuffer(indexBuffer.Indices.data(), indexBuffer.Indices.size());
    Internal::UnbindIndexBuffer();
    return openGLId;
}

struct VertexArray {};
Storage<VertexBuffer, IndexBuffer, VertexArray> g_storage;
} // namespace

VertexArrayId CreateVertexArray(
    const VertexBuffer& vertexBuffer, const IndexBuffer& indexBuffer) {
    unsigned int openGLVertexArray;
    Internal::InitialiseVertexArray(&openGLVertexArray);
    Internal::BindVertexArray(openGLVertexArray);

    unsigned int openGLVertexBuffer = CreateVertexBuffer(vertexBuffer);
    unsigned int openGLIndexBuffer = CreateIndexBuffer(indexBuffer);

    Internal::UnbindVertexArray(openGLVertexArray);

    return AddStorageEntry(
        g_storage, std::make_tuple(
                    std::make_pair(vertexBuffer, openGLVertexBuffer),
                    std::make_pair(indexBuffer, openGLIndexBuffer),
                    std::make_pair(VertexArray{}, openGLVertexArray)));

}
} // namespace GraphicLib