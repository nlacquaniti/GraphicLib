#include "GraphicLib/VertexArray.h"

#include "GraphicLib/IndexBuffer.h"
#include "GraphicLib/VertexBuffer.h"
#include "InternalLogger.h"
#include <limits>

#ifdef OPENGL_IMPL
#include "OpenGLImpl/VertexArrayImpl.h"
using VertexArrayImpl = GraphicLib::OpenGLImpl::VertexArrayImpl;
using GraphicAPI = GraphicLib::OpenGLImpl::API;
#else
#error "No VertexArrayImpl has been detected."
#endif

namespace GraphicLib {
void VertexArray::Initialise() {
    GraphicAPI::Get().VertexArray().Initialise()
    VertexArrayImpl::Initialise(_id);
    _vertexBuffer.Initialise();
    _indexBuffer.Initialise();
}

void VertexArray::Bind() {
    VertexArrayImpl::Bind(_id);
    _vertexBuffer.Bind();
    _indexBuffer.Bind();
}

void VertexArray::Unbind() {
    VertexArrayImpl::Unbind(_id);
    _vertexBuffer.Unbind();
    _indexBuffer.Unbind();
}

void VertexArray::Draw() {
    const auto trianglesCount = _indexBuffer.Get().Size() * 3;
    if (trianglesCount > std::numeric_limits<int>::max()) {
       LOG_INTERNAL_ERROR("Triangles count exceeded the max number");
        return;
    }
    VertexArrayImpl::Draw(_id, static_cast<int>(trianglesCount));
}

const VertexBuffer& VertexArray::GetVertexBuffer() const {
    return _vertexBuffer;
}

VertexBuffer& VertexArray::GetVertexBuffer() {
    return _vertexBuffer;
}

const IndexBuffer& VertexArray::GetIndexBuffer() const {
    return _indexBuffer;
}

IndexBuffer& VertexArray::GetIndexBuffer() {
    return _indexBuffer;
}
} // namespace GraphicLib
